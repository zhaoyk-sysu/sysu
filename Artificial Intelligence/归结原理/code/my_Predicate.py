import re
from collections import OrderedDict

# 解析单个文字（literal），返回谓词、参数和是否为否定形式
def parse_literal(literal_str):
    # 去除字符串首尾的空白字符
    literal_str = literal_str.strip()
    # 检查文字是否为否定形式
    is_negated = literal_str.startswith("~")
    if is_negated:
        # 去掉否定符号并去除首尾空白
        literal_str = literal_str[1:].strip()
    # 使用正则表达式匹配谓词和参数
    match = re.match(r"^([A-Z]\w*)\((.*)\)$", literal_str)
    if not match:
        # 若不匹配，返回文字本身、空参数和否定标志
        return literal_str, (), is_negated
    # 提取谓词和参数部分
    predicate, args_str = match.groups()
    # 将参数部分按逗号分割并去除首尾空白，若为空则返回空元组
    args = tuple(arg.strip() for arg in args_str.split(",")) if args_str else ()
    return predicate, args, is_negated

# 将文字转换为字符串表示
def literal_to_str(literal):
    # 解包文字的谓词、参数和否定标志
    predicate, args, is_negated = literal
    # 根据否定标志添加否定符号
    result = "~" if is_negated else ""
    # 若有参数，拼接谓词和参数；否则只返回谓词
    result += f"{predicate}({','.join(args)})" if args else predicate
    return result

# 将子句转换为字符串表示
def clause_to_str(clause):
    # 若子句为空，返回 "NIL"；否则拼接子句中的文字
    return "NIL" if not clause else "(" + ", ".join(literal_to_str(l) for l in clause) + ")"

class Sentences:
    def __init__(self, filepath):
        # 初始化知识库
        self.knowledge_base = []
        # 初始化查询列表
        self.queries = []
        # 初始化归结步骤记录
        self.resolution_steps = []
        # 从文件加载知识库和查询
        self.load_from_file(filepath)

    def load_from_file(self, filepath):
        with open(filepath, encoding='utf-8') as file:
            # 读取文件的所有行
            lines = file.readlines()
        # 标记当前是否在处理知识库
        processing_kb = True
        for line in lines:
            # 去除行首尾空白
            line = line.strip()
            if not line or line in {"KB:", "QUERY:"}:
                # 切换处理模式
                processing_kb = line != "QUERY:"
                continue
            # 解析当前行的子句
            clause = self.parse_clause(line)
            target_list = self.knowledge_base if processing_kb else self.queries
            if clause not in target_list:
                target_list.append(clause)
        # 将查询添加到知识库中
        self.knowledge_base.extend(self.queries)

    def parse_clause(self, text):
        # 去除首尾空白
        text = text.strip()
        if text.startswith("(") and text.endswith(")"):
            # 去掉括号
            text = text[1:-1].strip()
        # 解析子句中的每个文字
        return [parse_literal(part.strip()) for part in text.split(",") if part.strip()]

    def resolution(self):
        print("归结开始:")
        print("知识库:")
        for idx, clause in enumerate(self.knowledge_base, start=1):
            print(f"{idx}: {clause_to_str(clause)}")
        print("查询 (取反形式):")
        for clause in self.queries:
            print(clause_to_str(clause))
        print()

        # 按子句长度对知识库子句进行排序
        kb_list = sorted(self.knowledge_base, key=len)
        seen_clauses = {frozenset(clause) for clause in kb_list}
        step_counter = 0
        new_clauses_added = True

        while new_clauses_added:
            new_clauses_added = False
            for i in range(len(kb_list)):
                for j in range(i + 1, len(kb_list)):
                    new_resolvents = self.resolve(kb_list[i], kb_list[j])
                    for new_clause, substitution in new_resolvents:
                        step_counter += 1
                        step_log = f"[步骤 {step_counter}] 归结: {clause_to_str(kb_list[i])} 与 {clause_to_str(kb_list[j])} => {clause_to_str(new_clause)}，合一: {substitution}"
                        print(step_log)
                        self.resolution_steps.append(step_log)
                        if not new_clause:
                            print("得到空子句 (NIL)，归结成功！")
                            return
                        frozen_clause = frozenset(new_clause)
                        if frozen_clause not in seen_clauses:
                            seen_clauses.add(frozen_clause)
                            kb_list.append(new_clause)
                            # 新添加子句后重新按长度排序
                            kb_list = sorted(kb_list, key=len)
                            new_clauses_added = True
            if not new_clauses_added:
                print("归结失败，无法推出空子句。")
                return

    def resolve(self, clause1, clause2):
        # 存储归结结果
        resolvents = []
        for i, lit1 in enumerate(clause1):
            for j, lit2 in enumerate(clause2):
                if lit1[0] == lit2[0] and lit1[2] != lit2[2]:
                    # 尝试对文字进行合一操作
                    substitution = self.literal_unify(lit1, lit2)
                    if substitution is not None:
                        new_clause = OrderedDict.fromkeys(
                            self.apply_substitution(lit, substitution)
                            for k, lit in enumerate(clause1 + clause2)
                            if k != i and k != (j + len(clause1))
                        )
                        resolvents.append((list(new_clause.keys()), substitution))
        return resolvents

    def literal_unify(self, lit1, lit2):
        # 提取两个文字的谓词和参数
        pred1, args1, _ = lit1
        pred2, args2, _ = lit2
        # 检查谓词和参数数量是否一致
        if pred1 != pred2 or len(args1) != len(args2):
            return None
        # 初始化替换字典
        substitution = {}
        for arg1, arg2 in zip(args1, args2):
            # 对参数进行合一操作
            substitution = self.unify(arg1, arg2, substitution)
            if substitution is None:
                return None
        return substitution

    def unify(self, x, y, subst):
        # 初始化栈用于存储待处理的变量对
        stack = [(x, y)]
        while stack:
            x, y = stack.pop()
            if x == y:
                continue
            if self.is_variable(x):
                if x in subst:
                    stack.append((subst[x], y))
                else:
                    subst[x] = y
            elif self.is_variable(y):
                if y in subst:
                    stack.append((x, subst[y]))
                else:
                    subst[y] = x
            else:
                return None
        return subst

    def is_variable(self, token):
        # 判断是否为单个小写字母
        return len(token) == 1 and token.islower()

    def apply_substitution(self, literal, subst):
        # 解包文字的谓词、参数和否定标志
        pred, args, neg = literal
        # 对参数应用替换
        new_args = tuple(subst.get(arg, arg) for arg in args)
        return pred, new_args, neg

    