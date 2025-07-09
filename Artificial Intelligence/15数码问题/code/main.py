import heapq
import numpy as np
import argparse
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import random


def is_solvable(puzzle):
    # 计算逆序对的数量
    inversions = 0
    for i in range(16):
        for j in range(i + 1, 16):
            if puzzle[j] and puzzle[i] and puzzle[i] > puzzle[j]:
                inversions += 1
    # 找到空格的位置
    empty_row = 4 - (puzzle.index(0) // 4)
    # 判断是否可解
    return (inversions % 2 == 0) == (empty_row % 2 == 1)


def generate_random_puzzle():
    puzzle = list(range(16))
    random.shuffle(puzzle)
    while not is_solvable(puzzle):
        random.shuffle(puzzle)
    return puzzle


def convert_1d_to_2d(puzzle_1d):
    return [puzzle_1d[i:i + 4] for i in range(0, 16, 4)]


# 目标状态，也就是谜题最终要达到的样子
GOAL_STATE = [[1, 2, 3, 4],
              [5, 6, 7, 8],
              [9, 10, 11, 12],
              [13, 14, 15, 0]]

# 生成随机初始状态，确保20步内可解
while True:
    random_puzzle_1d = generate_random_puzzle()
    INITIAL_STATE = convert_1d_to_2d(random_puzzle_1d)
    start_manhattan_distance = sum(
        abs((value - 1) // 4 - i) + abs((value - 1) % 4 - j)
        for i in range(4)
        for j in range(4)
        for value in [INITIAL_STATE[i][j]]
        if value != 0
    )
    if start_manhattan_distance < 20:
        break

# 将二维的状态数组转换为一维元组，方便后续操作和比较
def convert_state_to_tuple(state):
    return tuple([element for sub_array in state for element in sub_array])


# 找到空白方块（值为 0）在状态数组中的位置
def locate_zero(state):
    for i in range(4):
        for j in range(4):
            if state[i][j] == 0:
                return i, j


# 根据当前状态，生成所有可能的移动方向
def generate_possible_moves(state):
    possible_moves = []
    zero_row, zero_col = locate_zero(state)

    # 空白方块向上移动
    if zero_row > 0:
        possible_moves.append("up")
    # 空白方块向下移动
    if zero_row < 3:
        possible_moves.append("down")
    # 空白方块向左移动
    if zero_col > 0:
        possible_moves.append("left")
    # 空白方块向右移动
    if zero_col < 3:
        possible_moves.append("right")

    return possible_moves


# 对当前状态应用指定的移动，返回移动后的新状态
def apply_movement(state, move):
    zero_row, zero_col = locate_zero(state)
    # 复制当前状态，避免修改原始状态
    new_state = [row[:] for row in state]

    if move == "up":
        new_state[zero_row][zero_col], new_state[zero_row - 1][zero_col] = new_state[zero_row - 1][zero_col], new_state[zero_row][zero_col]
    elif move == "down":
        new_state[zero_row][zero_col], new_state[zero_row + 1][zero_col] = new_state[zero_row + 1][zero_col], new_state[zero_row][zero_col]
    elif move == "left":
        new_state[zero_row][zero_col], new_state[zero_row][zero_col - 1] = new_state[zero_row][zero_col - 1], new_state[zero_row][zero_col]
    elif move == "right":
        new_state[zero_row][zero_col], new_state[zero_row][zero_col + 1] = new_state[zero_row][zero_col + 1], new_state[zero_row][zero_col]

    return new_state


# 启发式函数，计算当前状态到目标状态的曼哈顿距离
def calculate_manhattan_distance(state):
    total_distance = 0
    for i in range(4):
        for j in range(4):
            value = state[i][j]
            if value != 0:
                # 计算目标位置
                target_row = (value - 1) // 4
                target_col = (value - 1) % 4
                total_distance += abs(target_row - i) + abs(target_col - j)
    return total_distance


# 使用 A* 算法来解决 15 - 谜题
def a_star_search(start_state):
    start_state_tuple = convert_state_to_tuple(start_state)
    goal_state_tuple = convert_state_to_tuple(GOAL_STATE)

    # A* 算法的优先队列，用最小堆实现
    open_list = []
    heapq.heappush(open_list, (calculate_manhattan_distance(start_state), 0, start_state_tuple, []))
    # 记录已经访问过的状态
    visited = set()
    visited.add(start_state_tuple)

    while open_list:
        # 取出 f 值（g + h）最小的状态
        f, g, current_state_tuple, path = heapq.heappop(open_list)
        current_state = [list(current_state_tuple[i:i + 4]) for i in range(0, len(current_state_tuple), 4)]

        # 检查是否到达目标状态
        if current_state_tuple == goal_state_tuple:
            return path

        # 生成所有可能的移动
        for move in generate_possible_moves(current_state):
            new_state = apply_movement(current_state, move)
            new_state_tuple = convert_state_to_tuple(new_state)

            # 如果新状态未被访问过
            if new_state_tuple not in visited:
                visited.add(new_state_tuple)
                new_path = path + [move]
                heapq.heappush(open_list, (g + 1 + calculate_manhattan_distance(new_state), g + 1, new_state_tuple, new_path))


# 使用 IDA* 算法来解决 15 - 谜题
def ida_star_search(start_state):
    start_state_tuple = convert_state_to_tuple(start_state)
    goal_state_tuple = convert_state_to_tuple(GOAL_STATE)

    # 初始阈值为初始状态的曼哈顿距离
    threshold = calculate_manhattan_distance(start_state)

    def recursive_search(path, g, threshold):
        current_state_tuple = path[-1]
        current_state = [list(current_state_tuple[i:i + 4]) for i in range(0, len(current_state_tuple), 4)]

        f = g + calculate_manhattan_distance(current_state)

        # 如果 f 值超过阈值，返回 f 值
        if f > threshold:
            return f

        # 如果到达目标状态，返回路径
        if current_state_tuple == goal_state_tuple:
            moves = []
            for i in range(len(path) - 1):
                current = [list(path[i][j:j + 4]) for j in range(0, len(path[i]), 4)]
                next_state = [list(path[i + 1][j:j + 4]) for j in range(0, len(path[i + 1]), 4)]
                for move in generate_possible_moves(current):
                    if apply_movement(current, move) == next_state:
                        moves.append(move)
                        break
            return moves

        min_threshold = float('inf')
        for move in generate_possible_moves(current_state):
            new_state = apply_movement(current_state, move)
            new_state_tuple = convert_state_to_tuple(new_state)

            # 如果新状态未在路径中
            if new_state_tuple not in path:
                path.append(new_state_tuple)
                result = recursive_search(path, g + 1, threshold)
                if isinstance(result, list):
                    return result
                min_threshold = min(min_threshold, result)
                path.pop()

        return min_threshold

    # 初始化搜索
    path = [start_state_tuple]
    while True:
        result = recursive_search(path, 0, threshold)
        if isinstance(result, list):
            return result
        # 更新阈值
        threshold = result


# 根据初始状态和用户选择，决定使用 A* 还是 IDA* 算法
def select_algorithm(start_state, use_ida_star=False):
    if use_ida_star:
        print("选择 IDA* 算法")
        return ida_star_search(start_state)
    else:
        start_manhattan_distance = calculate_manhattan_distance(start_state)
        print(f"初始曼哈顿距离: {start_manhattan_distance}")

        # 如果初始曼哈顿距离小于15，使用 A* 算法
        if start_manhattan_distance < 15:
            print("选择 A* 算法")
            return a_star_search(start_state)
        else:
            print("选择 IDA* 算法")
            return ida_star_search(start_state)


# 可视化谜题的解题过程
def visualize_solution(solution, initial_state):
    states = [initial_state]
    current_state = initial_state
    # 依次应用每一步移动，记录所有状态
    for move in solution:
        current_state = apply_movement(current_state, move)
        states.append(current_state)

    fig, ax = plt.subplots()
    # 设置坐标轴范围
    ax.set_xlim(-0.5, 3.5)
    ax.set_ylim(-0.5, 3.5)
    # 设置坐标轴刻度
    ax.set_xticks(np.arange(0, 4, 1))
    ax.set_yticks(np.arange(0, 4, 1))
    # 隐藏刻度标签
    ax.set_xticklabels([])
    ax.set_yticklabels([])
    # 显示网格线
    ax.grid(True)

    def update(frame):
        ax.clear()
        ax.set_xlim(-0.5, 3.5)
        ax.set_ylim(-0.5, 3.5)
        ax.set_xticks(np.arange(0, 4, 1))
        ax.set_yticks(np.arange(0, 4, 1))
        ax.set_xticklabels([])
        ax.set_yticklabels([])
        ax.grid(True)
        state = states[frame]
        for i in range(4):
            for j in range(4):
                value = state[i][j]
                if value != 0:
                    ax.text(j, 3 - i, str(value), ha='center', va='center', fontsize=20)

    # 创建动画
    ani = FuncAnimation(fig, update, frames=len(states), interval=500, repeat=False)
    plt.show()


# 主函数
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="15-Puzzle Solver")
    parser.add_argument("--ida_star", action="store_true", help="使用 IDA* 算法")
    args = parser.parse_args()

    solution = select_algorithm(INITIAL_STATE, use_ida_star=args.ida_star)
    print("解决方案:", solution)
    visualize_solution(solution, INITIAL_STATE)
