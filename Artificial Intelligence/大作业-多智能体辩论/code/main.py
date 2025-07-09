from typing import List, Dict, Any, TypedDict, Union
from datetime import datetime
import json
import random
from openai import OpenAI  # 引入用户已部署的OpenAI库
from graphviz import Digraph  # 新增：用于创建计算图
import os

# 初始化Ollama客户端
client = OpenAI(
    base_url="http://localhost:11434/v1",
    api_key="ollama"
)

# 实现chat函数
def chat(messages: List[Dict[str, str]]) -> str:
    response = client.chat.completions.create(
        model="deepseek-r1:8b",
        messages=messages,
        stream=False
    )
    return response.choices[0].message.content

# 定义RAG检索工具
def debate_rag(query: str, graph: Digraph = None) -> str:
    """通过Ollama API检索辩论知识库，并记录到计算图"""
    knowledge_base = {
        "人工智能伦理": "支持观点：AI需伦理框架防止滥用；反对观点：伦理限制技术创新",
        "环境保护政策": "支持观点：严格政策可遏制气候变化；反对观点：增加企业成本阻碍经济",
        "在线教育优势": "支持观点：打破地域限制提升普及率；反对观点：缺乏面对面互动影响效果"
    }
    
    for key in knowledge_base:
        if key in query:
            if graph:
                graph.node("RAG", "RAG检索工具", shape="box", style="filled", fillcolor="lightblue")
            return knowledge_base[key]
    
    system_prompt = f"你是辩论知识助手，生成{query}的1条支持和反对观点，每条不超过30字"
    if graph:
        graph.node("RAG", "RAG检索工具", shape="box", style="filled", fillcolor="lightblue")
        graph.edge("LLM", "RAG", label="查询:" + query[:10] + "...")
    response = chat([
        {"role": "system", "content": system_prompt},
        {"role": "user", "content": query}
    ])
    return response

# 定义搜索引擎工具
def search_engine(query: str, graph: Digraph = None) -> str:
    """模拟搜索引擎获取实时数据，并记录到计算图"""
    search_database = {
        "AI伦理监管政策": "欧盟AI法案要求高风险系统需伦理审查，美国NIST发布AI风险管理框架",
        "环保政策经济影响": "世界银行研究显示：严格环保政策可使长期GDP增长1.5%，短期企业成本增加8%",
        "在线教育用户增长": "2024年全球在线教育用户达12亿，较2020年增长80%，亚洲市场占比55%"
    }
    
    for key in search_database:
        if key in query:
            if graph:
                graph.node("Search", "搜索引擎", shape="box", style="filled", fillcolor="lightgreen")
            return search_database[key]
    
    if graph:
        graph.node("Search", "搜索引擎", shape="box", style="filled", fillcolor="lightgreen")
        graph.edge("LLM", "Search", label="查询:" + query[:10] + "...")
    return f"搜索引擎提示：关于{query}的最新数据未找到，建议使用更具体关键词"

# 定义辩论状态类型
class DebateState(TypedDict):
    messages: List[Dict[str, str]]       # 对话历史
    current_speaker: str                # 当前发言者
    topic: str                          # 辩论主题
    round: int                          # 轮次
    max_rounds: int                     # 最大轮次
    affirmative_points: List[str]       # 正方论点库
    negative_points: List[str]          # 反方论点库
    judge_feedback: List[str]           # 裁判反馈
    audience_reviews: List[str]         # 观众评价
    terminated: bool                    # 是否结束
    graph: Digraph                      # 新增：计算图对象

# 定义智能体基础类（增强记忆机制应用）
class DebateAgent:
    def __init__(self, name: str, role: str, system_prompt: str):
        self.name = name
        self.role = role
        self.system_prompt = system_prompt
        self.short_term_memory: List[Dict] = []  # 短期记忆：最近5轮对话
        self.long_term_memory: Dict = {           # 长期记忆：辩论策略库
            "argument_strategies": {
                "事实论证": "引用数据或案例支持观点",
                "因果论证": "阐述事件因果关系强化逻辑",
                "类比论证": "通过相似案例类比增强说服力"
            },
            "topic_knowledge": {
                "科技伦理": ["AI透明性", "算法偏见", "责任归属"],
                "环境保护": ["碳中和目标", "可再生能源占比", "碳交易机制"],
                "教育技术": ["混合式学习", "个性化推荐", "学习效果评估"]
            }
        }
    
    def update_short_term_memory(self, message: Dict):
        """更新短期记忆（保持最近5条）"""
        self.short_term_memory.append(message)
        if len(self.short_term_memory) > 8:
            self.short_term_memory.pop(0)
    
    def get_context(self, state: DebateState) -> List[Dict[str, str]]:
        """构建上下文：系统提示+短期记忆+辩论状态+策略选择"""
        memory_str = "\n".join([f"{m['agent']}: {m['content']}" for m in self.short_term_memory])
        topic_info = f"辩论主题：{state['topic']}"
        round_info = f"当前轮次：{state['round']}/{state['max_rounds']}"
        opponent_points = self._get_opponent_points(state)
        
        # 从长期记忆中选择论证策略（增强推理规划）
        strategy_type, strategy_desc = random.choice(list(self.long_term_memory["argument_strategies"].items()))
        
        context = [
            {"role": "system", "content": self.system_prompt},
            {"role": "user", "content": f"""
{topic_info}
{round_info}
对方已提出论点：{opponent_points}
近期对话记录：
{memory_str}
请使用【{strategy_type}】策略（{strategy_desc}）组织回应。
"""}
        ]
        
        # 记录到计算图
        if state.get('graph'):
            state['graph'].node(self.name, self.name, shape="ellipse", style="filled", 
                               fillcolor="lightyellow" if self.role == "正方" else "lightpink")
            state['graph'].node("LLM", "LLM推理", shape="box3d", style="filled", fillcolor="lightgray")
            state['graph'].edge(self.name, "LLM", label="生成上下文")
        
        return context
    
    def _get_opponent_points(self, state: DebateState) -> str:
        """获取对方论点（根据角色动态调整）"""
        if self.role == "正方":
            return ", ".join(state["negative_points"][-2:]) or "对方尚未提出明确论点"
        elif self.role == "反方":
            return ", ".join(state["affirmative_points"][-2:]) or "对方尚未提出明确论点"
        else:  # 裁判或观众
            return f"正方：{', '.join(state['affirmative_points'][-2:]) or '无'}；反方：{', '.join(state['negative_points'][-2:]) or '无'}"

# 创建辩论智能体
affirmative = DebateAgent(
    "正方辩手",
    "正方",
    """你是辩论正方辩手。你的任务是：
1. 坚定支持辩论主题，构建逻辑严密的论点体系
2. 针对反方论点进行反驳，指出其逻辑漏洞
3. 优先使用事实数据或权威案例支持观点
发言格式：【论点】观点陈述 + 【论据】数据/案例支持 + 【总结】强调观点重要性"""
)

negative = DebateAgent(
    "反方辩手",
    "反方",
    """你是辩论反方辩手。你的任务是：
1. 全面反驳辩论主题，从多角度构建反对论点
2. 拆解正方论点的前提假设和推理过程
3. 可使用归谬法或类比法削弱对方论证
发言格式：【反驳】针对对方XX观点 + 【质疑】逻辑漏洞说明 + 【替代方案】我方观点阐述"""
)

judge = DebateAgent(
    "裁判",
    "裁判",
    """你是辩论裁判。你的任务是：
1. 客观评估双方论点的逻辑严密性和论据有效性
2. 每两轮给出一次反馈，指出双方优势与不足
3. 关注论点是否紧扣主题，避免偏离核心议题
反馈格式：【正方优势】... 【反方优势】... 【改进建议】..."""
)

audience = DebateAgent(
    "观众代表",
    "观众",
    """你是一位专业的辩论观察员。你的任务是：
1. 评估辩论的精彩程度和双方表现
2. 关注论点创新性、逻辑连贯性和语言感染力
3. 给出具体评价和改进建议
评价格式：【精彩度】0-10分 + 【亮点】... 【不足】... 【建议】..."""
)

def affirmative_node(state: DebateState) -> Dict:
    """正方发言节点（整合双工具调用）"""
    context = affirmative.get_context(state)
    
    # 调用RAG检索工具
    rag_result = debate_rag(state["topic"], state.get('graph'))
    context[1]["content"] += f"\nRAG论点支持：{rag_result}"
    
    # 调用搜索引擎工具（新增工具调用）
    search_result = search_engine(state["topic"], state.get('graph'))
    context[1]["content"] += f"\n搜索引擎数据：{search_result}"
    
    response_content = chat(context)
    
    message = {
        "agent": affirmative.name,
        "content": response_content,
        "timestamp": datetime.now().isoformat()
    }
    
    affirmative.update_short_term_memory(message)
    state["messages"].append(message)
    state["current_speaker"] = affirmative.name
    state["round"] += 1
    
    # 提取新论点
    if "【论点】" in response_content:
        new_point = response_content.split("【论点】")[-1].split("【论据】")[0].strip()
        state["affirmative_points"].append(new_point)
    
    print(f"\n{affirmative.name}: {response_content}")
    
    # 记录到计算图
    if state.get('graph'):
        state['graph'].edge("LLM", affirmative.name, label="生成回应")
        state['graph'].edge("RAG", affirmative.name, label="论点支持")
        state['graph'].edge("Search", affirmative.name, label="数据支持")
    
    return {"state": state, "next": "negative"}

def negative_node(state: DebateState) -> Dict:
    """反方发言节点（双工具调用）"""
    context = negative.get_context(state)
    
    # 调用RAG检索工具
    rag_result = debate_rag(state["topic"], state.get('graph'))
    context[1]["content"] += f"\nRAG反驳支持：{rag_result}"
    
    # 调用搜索引擎工具
    search_result = search_engine(state["topic"], state.get('graph'))
    context[1]["content"] += f"\n搜索引擎数据：{search_result}"
    
    response_content = chat(context)
    
    message = {
        "agent": negative.name,
        "content": response_content,
        "timestamp": datetime.now().isoformat()
    }
    
    negative.update_short_term_memory(message)
    state["messages"].append(message)
    state["current_speaker"] = negative.name
    
    # 提取新反驳点
    if "【反驳】" in response_content:
        new_counter = response_content.split("【反驳】")[-1].split("【质疑】")[0].strip()
        state["negative_points"].append(new_counter)
    
    print(f"\n{negative.name}: {response_content}")
    
    # 记录到计算图
    if state.get('graph'):
        state['graph'].edge("LLM", negative.name, label="生成回应")
        state['graph'].edge("RAG", negative.name, label="反驳支持")
        state['graph'].edge("Search", negative.name, label="数据支持")
    
    # 每三轮触发观众评价
    if state["round"] % 3 == 0 and state["round"] < state["max_rounds"]:
        return {"state": state, "next": "audience"}
    # 每两轮触发裁判反馈
    elif state["round"] % 2 == 0 and state["round"] < state["max_rounds"]:
        return {"state": state, "next": "judge"}
    else:
        return {"state": state, "next": "affirmative"}

def judge_node(state: DebateState) -> Dict:
    """裁判反馈节点"""
    context = judge.get_context(state)
    points_summary = f"正方论点：{', '.join(state['affirmative_points'][-2:])}\n反方论点：{', '.join(state['negative_points'][-2:])}"
    context[1]["content"] += f"\n当前论点总结：\n{points_summary}"
    
    response_content = chat(context)
    
    message = {
        "agent": judge.name,
        "content": response_content,
        "timestamp": datetime.now().isoformat()
    }
    
    judge.update_short_term_memory(message)
    state["messages"].append(message)
    state["judge_feedback"].append(response_content)
    state["current_speaker"] = judge.name
    
    print(f"\n{judge.name}: {response_content}")
    
    # 记录到计算图
    if state.get('graph'):
        state['graph'].edge("LLM", judge.name, label="生成反馈")
        state['graph'].edge(affirmative.name, judge.name, label="正方论点")
        state['graph'].edge(negative.name, judge.name, label="反方论点")
    
    if state["round"] < state["max_rounds"]:
        return {"state": state, "next": "affirmative"}
    else:
        return {"state": state, "next": None}

# 新增观众评价节点
def audience_node(state: DebateState) -> Dict:
    """观众评价节点"""
    context = audience.get_context(state)
    points_summary = f"正方论点：{', '.join(state['affirmative_points'][-3:])}\n反方论点：{', '.join(state['negative_points'][-3:])}"
    context[1]["content"] += f"\n当前论点总结：\n{points_summary}"
    
    if state["judge_feedback"]:
        latest_judge_feedback = state["judge_feedback"][-1]
        context[1]["content"] += f"\n最新裁判反馈：{latest_judge_feedback}"
    
    response_content = chat(context)
    
    message = {
        "agent": audience.name,
        "content": response_content,
        "timestamp": datetime.now().isoformat()
    }
    
    audience.update_short_term_memory(message)
    state["messages"].append(message)
    state["audience_reviews"].append(response_content)
    state["current_speaker"] = audience.name
    
    print(f"\n{audience.name}: {response_content}")
    
    # 记录到计算图
    if state.get('graph'):
        state['graph'].edge("LLM", audience.name, label="生成评价")
        state['graph'].edge(affirmative.name, audience.name, label="正方论点")
        state['graph'].edge(negative.name, audience.name, label="反方论点")
        state['graph'].edge(judge.name, audience.name, label="裁判反馈")
    
    if state["round"] < state["max_rounds"]:
        return {"state": state, "next": "affirmative"}
    else:
        return {"state": state, "next": None}

# 生成计算图
def generate_computation_graph(state: DebateState, output_file: str = "debate_computation_graph"):
    """生成并渲染辩论计算图"""
    if not state.get('graph'):
        return
    
    # 设置中文字体支持
    if os.name == 'nt':  # Windows系统
        state['graph'].attr(fontname='SimHei')
    elif os.name == 'posix':  # Linux或macOS系统
        state['graph'].attr(fontname='WenQuanYi Micro Hei')
    
    # 添加状态转换边
    state_transitions = [
        ("正方辩手", "反方辩手", "发言顺序"),
        ("反方辩手", "裁判", "两轮后"),
        ("反方辩手", "观众代表", "三轮后"),
        ("裁判", "正方辩手", "反馈后"),
        ("观众代表", "正方辩手", "评价后")
    ]
    
    for from_node, to_node, label in state_transitions:
        if from_node in [n.attr['label'] for n in state['graph'].nodes()] and \
           to_node in [n.attr['label'] for n in state['graph'].nodes()]:
            state['graph'].edge(from_node, to_node, label=label)
    
    # 渲染图形
    state['graph'].render(output_file, format='png', cleanup=True, view=False)
    print(f"计算图已保存至 {output_file}.png")

# 运行辩论流程
def run_debate_workflow():
    """基于状态机的辩论流程（含Markdown输出和计算图）"""
    debate_topic = "人工智能应否受到严格伦理监管"
    
    # 初始化计算图
    graph = Digraph('DebateComputationGraph', filename='debate_graph.gv', node_attr={'fontname': 'SimHei'})
    graph.attr(rankdir='TB', size='12,10', dpi='300', fontname='SimHei')
    
    state: DebateState = {
        "messages": [{
            "agent": "System",
            "content": f"辩论主题：{debate_topic}\n现在开始辩论，正方先发言。",
            "timestamp": datetime.now().isoformat()
        }],
        "current_speaker": "正方辩手",
        "topic": debate_topic,
        "round": 0,
        "max_rounds": 5,
        "affirmative_points": [],
        "negative_points": [],
        "judge_feedback": [],
        "audience_reviews": [],  # 新增观众评价列表
        "terminated": False,
        "graph": graph  # 新增：计算图对象
    }
    print(f"\n=== 辩论主题 ===\n{debate_topic}\n")
    print("系统: 现在开始辩论，正方先发言。\n")
    
    current_agent = "affirmative"
    while state["round"] < state["max_rounds"] and not state["terminated"]:
        if current_agent == "affirmative":
            output = affirmative_node(state)
        elif current_agent == "negative":
            output = negative_node(state)
        elif current_agent == "judge":
            output = judge_node(state)
        else:  # audience
            output = audience_node(state)
        
        state = output["state"]
        current_agent = output["next"] if output["next"] else "terminated"
        print("-" * 50)
    
    # 输出辩论总结
    if state["judge_feedback"]:
        print("\n=== 辩论总结 ===")
        print(f"裁判最终反馈：{state['judge_feedback'][-1]}")
    else:
        print("\n=== 辩论未完成 ===")
    
    if state["audience_reviews"]:
        print("\n=== 观众评价 ===")
        for review in state["audience_reviews"]:
            print(f"- {review}")
    
    # 保存对话历史（JSON和Markdown双格式）
    with open("debate_history.json", "w", encoding="utf-8") as f:
        json.dump(state["messages"], f, ensure_ascii=False, indent=2)
    
    with open("debate_report.md", "w", encoding="utf-8") as f:
        f.write("# 多智能体辩论系统实验报告\n\n")
        f.write(f"## 辩论主题：{debate_topic}\n\n")
        f.write("## 智能体分工\n\n")
        f.write("- **正方辩手**：支持论点构建与反驳\n")
        f.write("- **反方辩手**：反对论点构建与拆解\n")
        f.write("- **裁判**：论点评估与反馈\n")
        f.write("- **观众代表**：辩论精彩度评价\n\n")
        f.write("## 对话历史记录\n\n")
        for msg in state["messages"]:
            time = msg["timestamp"].split("T")
            f.write(f"**{msg['agent']}** ({time[0]} {time[1].split('.')[0]})\n")
            f.write(f"{msg['content']}\n\n")
            f.write("---\n\n")
        
        f.write("## 论点与工具使用分析\n\n")
        f.write("### 正方论点库\n")
        for i, point in enumerate(state["affirmative_points"], 1):
            f.write(f"{i}. {point}\n")
        
        f.write("\n### 反方论点库\n")
        for i, point in enumerate(state["negative_points"], 1):
            f.write(f"{i}. {point}\n")
        
        f.write("\n### 工具调用记录\n")
        f.write("- **RAG检索工具**：获取辩论知识库论点\n")
        f.write("- **搜索引擎工具**：获取实时政策与数据支持\n\n")
        
        f.write("## 裁判反馈汇总\n")
        for feedback in state["judge_feedback"]:
            f.write(f"- {feedback}\n\n")
        
        f.write("## 观众评价汇总\n")
        for review in state["audience_reviews"]:
            f.write(f"- {review}\n\n")
    
    print("\n对话历史已保存至 debate_history.json")
    print("实验报告已生成至 debate_report.md")
    
    # 生成计算图
    generate_computation_graph(state)

# 主函数
if __name__ == "__main__":
    print("\n=== 多智能体辩论系统（带计算图功能）启动 ===")
    run_debate_workflow()