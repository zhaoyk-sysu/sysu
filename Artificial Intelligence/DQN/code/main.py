import argparse
import gymnasium as gym
from argument import dqn_arguments
import os
from agent_dir.agent_dqn import AgentDQN
from tqdm import tqdm


parser = argparse.ArgumentParser(description="dqn for cartpole")
parser = dqn_arguments(parser)  

def do_train(args):
    env_name = args.env_name
    env = gym.make(env_name)
    agent = AgentDQN(env, args)
    agent.train()

def do_test(args):
    env = gym.make(args.env_name, render_mode='human')
    agent = AgentDQN(env, args)

    # 加载训练好的模型权重
    agent.load_model()

    agent.init_game_setting()  # 关闭epsilon探索，直接利用策略

    done = False
    total_reward = 0
    s, _ = env.reset()
    while not done:
        env.render()
        a = agent.make_action(s, test=True)
        s, r, done, truncated, _ = env.step(a)
        total_reward += r
        if done or truncated:
            break
    env.close()
    print('Test total reward:', total_reward)


if __name__ == '__main__':
    args = parser.parse_args([])  # 不从命令行读取，方便调试

    # 这里控制是否训练或测试
    args.train_dqn = True
    args.test = False

    # 设置模型保存路径（必须和训练时一致）
    if not hasattr(args, 'save_path') or args.save_path is None:
        args.save_path = './model/dqn_cartpole.pth'

    print("是否训练:", args.train_dqn)
    print("是否测试:", args.test)

    if args.train_dqn:
        print("进入训练")
        do_train(args)

    if args.test:
        print("进入测试")
        do_test(args)
        
