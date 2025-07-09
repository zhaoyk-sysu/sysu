import os
import random
import copy
import numpy as np
import torch
import torch.nn.functional as F
from pathlib import Path
from torch import nn, optim
from agent_dir.agent import Agent
from collections import deque
from tqdm import tqdm
import logging

class QNetwork(nn.Module):
    def __init__(self, input_size, hidden_size, output_size):
        '''
        初始化Q网network
        '''
        super(QNetwork, self).__init__()
        self.fc1 = nn.Linear(input_size, hidden_size)
        self.fc2 = nn.Linear(hidden_size, output_size)

    def forward(self, inputs):
        '''
        forward函数
        '''
        x = F.relu(self.fc1(inputs))
        return self.fc2(x)
    
    def set_device(self, device: torch.device) -> torch.nn.Module:
        _model = self.to(device)
        _model.device = device
        return _model

    def save(self, path: str):
        torch.save(self.state_dict(), path)

    def load(self, path: str):
        self.load_state_dict(torch.load(path))


class ReplayBuffer:
    def __init__(self, buffer_size):
        self.buffer_size = buffer_size
        self.buffer = deque(maxlen=buffer_size)

    def __len__(self):
        return len(self.buffer)
    
    def full(self):
        return len(self.buffer) == self.buffer_size

    def push(self, *transition):
        self.buffer.append(transition)

    def sample(self, batch_size):
        samples = random.sample(self.buffer, batch_size)
        return zip(*samples)

    def clean(self):
        self.buffer.clear()


class AgentDQN(Agent):
    def __init__(self, env, args):
        super(AgentDQN, self).__init__(env)

        self.env = env
        self.args = args

        self.device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

        self.gamma = args.gamma
        self.batch_size = args.batch_size
        self.lr = args.lr
        self.epsilon = args.epsilon
        self.epsilon_decay = args.epsilon_decay
        self.epsilon_min = args.epsilon_min
        self.target_update_freq = args.target_update_freq
        self.memory_capacity = args.memory_capacity
        self.hidden_size = args.hidden_size
        self.save_path = args.save_path

        self.obs_dim = env.observation_space.shape[0]
        self.action_dim = env.action_space.n

        self.behavior_net = QNetwork(self.obs_dim, self.hidden_size, self.action_dim).set_device(self.device)
        self.target_net = QNetwork(self.obs_dim, self.hidden_size, self.action_dim).set_device(self.device)
        self.target_net.load_state_dict(self.behavior_net.state_dict())

        self.buffer = ReplayBuffer(self.memory_capacity)
        self.optimizer = optim.Adam(self.behavior_net.parameters(), lr=self.lr)

        self.steps = 0

    def init_game_setting(self):
        self.epsilon = 0.0

    def train(self):
        episodes = self.args.episodes
        for ep in range(episodes):
            state, _ = self.env.reset()
            total_reward = 0
            done = False
            truncated = False
            while not done and not truncated:
                action = self.make_action(state)
                next_state, reward, done, truncated, _ = self.env.step(action)
                self.buffer.push(state, action, reward, next_state, done)
                state = next_state
                total_reward += reward

                if len(self.buffer) >= self.batch_size:
                    self.update()

                self.steps += 1
                if self.steps % self.target_update_freq == 0:
                    self.target_net.load_state_dict(self.behavior_net.state_dict())

            print(f"Episode {ep + 1}, Reward: {total_reward}, Epsilon: {self.epsilon:.3f}")

            if self.epsilon > self.epsilon_min:
                self.epsilon *= self.epsilon_decay

        # 训练结束保存模型
        os.makedirs(os.path.dirname(self.save_path), exist_ok=True)
        self.behavior_net.save(self.save_path)

    def make_action(self, observation, test=False):
        obs = torch.FloatTensor(observation).unsqueeze(0).to(self.device)
        if (not test) and (random.random() < self.epsilon):
            return random.randrange(self.action_dim)
        with torch.no_grad():
            q_values = self.behavior_net(obs)
            return q_values.argmax().item()

    def update(self):
        states, actions, rewards, next_states, dones = self.buffer.sample(self.batch_size)

        states = torch.FloatTensor(np.array(states)).to(self.device)
        actions = torch.LongTensor(actions).unsqueeze(1).to(self.device)
        rewards = torch.FloatTensor(rewards).unsqueeze(1).to(self.device)
        next_states = torch.FloatTensor(np.array(next_states)).to(self.device)
        dones = torch.FloatTensor(dones).unsqueeze(1).to(self.device)

        current_q = self.behavior_net(states).gather(1, actions)
        #是否使用目标网络
        """with torch.no_grad():
          next_q = self.behavior_net(next_states).max(1, keepdim=True)[0]
          expected_q = rewards + (1 - dones) * self.gamma * next_q   """
        with torch.no_grad():
            next_q = self.target_net(next_states).max(1, keepdim=True)[0]
            expected_q = rewards + (1 - dones) * self.gamma * next_q

        loss = F.mse_loss(current_q, expected_q)

        self.optimizer.zero_grad()
        loss.backward()
        self.optimizer.step()

    def load_model(self):
        print(f"Loading model from {self.save_path} ...")
        self.behavior_net.load(self.save_path)
        self.target_net.load_state_dict(self.behavior_net.state_dict())

