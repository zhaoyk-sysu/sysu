import torch
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import Dataset, DataLoader
import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
import matplotlib.pyplot as plt
from sklearn.metrics import r2_score

plt.rcParams['font.sans-serif'] = ['SimHei']


# 自定义数据集类
class HousePriceDataset(Dataset):
    def __init__(self, features, labels):
        self.features = torch.tensor(features, dtype=torch.float32)
        self.labels = torch.tensor(labels, dtype=torch.float32)

    def __len__(self):
        return len(self.features)

    def __getitem__(self, idx):
        return self.features[idx], self.labels[idx]


# 定义房价预测回归模型
class HousePricePredictor(nn.Module):
    def __init__(self):
        super().__init__()
        self.fc1 = nn.Linear(4, 100)
        self.relu = nn.ReLU()
        self.fc2 = nn.Linear(100, 50)
        self.fc3 = nn.Linear(50, 1)

    def forward(self, x):
        x = self.fc1(x)
        x = self.relu(x)
        x = self.fc2(x)
        x = self.relu(x)
        x = self.fc3(x)
        return x


# 加载数据
def load_data(file_path):
    return pd.read_csv(file_path).values


# 数据预处理
def preprocess_data(features, labels):
    X_train, X_test, y_train, y_test = train_test_split(features, labels, test_size=0.2, random_state=42)
    scaler_features = StandardScaler()
    scaler_labels = StandardScaler()
    X_train = scaler_features.fit_transform(X_train)
    X_test = scaler_features.transform(X_test)
    y_train = scaler_labels.fit_transform(y_train.reshape(-1, 1)).flatten()
    y_test = scaler_labels.transform(y_test.reshape(-1, 1)).flatten()
    return X_train, X_test, y_train, y_test


# 训练模型
def train_model(model, train_loader, criterion, optimizer, epochs):
    model.train()
    loss_values = []
    for epoch in range(epochs):
        epoch_loss = 0
        for inputs, labels in train_loader:
            optimizer.zero_grad()
            outputs = model(inputs)
            loss = criterion(outputs.squeeze(), labels)
            loss.backward()
            optimizer.step()
            epoch_loss += loss.item()
        epoch_loss /= len(train_loader)
        loss_values.append(epoch_loss)
        print(f'Epoch {epoch + 1}/{epochs}, Loss: {epoch_loss}')
    return loss_values


# 评估模型
def evaluate_model(model, test_loader, criterion):
    model.eval()
    y_pred_list, y_true_list = [], []
    total_loss = 0
    with torch.no_grad():
        for inputs, labels in test_loader:
            outputs = model(inputs)
            loss = criterion(outputs.squeeze(), labels)
            total_loss += loss.item()
            y_pred_list.extend(outputs.squeeze().numpy())
            y_true_list.extend(labels.numpy())
    y_pred, y_true = np.array(y_pred_list), np.array(y_true_list)
    mse = np.mean((y_true - y_pred) ** 2)
    r2 = r2_score(y_true, y_pred)
    print(f'Test Loss (MSE): {mse}')
    print(f'R^2 Score: {r2}')
    return y_true, y_pred


if __name__ == "__main__":
    file_path = "D:\大二下\人工智能资料\实验课\lab_7_pytorch和MLP\house_price.csv"
    data = load_data(file_path)
    features, labels = data[1:, :-1], data[1:, -1]
    X_train, X_test, y_train, y_test = preprocess_data(features, labels)

    train_dataset = HousePriceDataset(X_train, y_train)
    test_dataset = HousePriceDataset(X_test, y_test)

    train_loader = DataLoader(train_dataset, batch_size=64, shuffle=True)
    test_loader = DataLoader(test_dataset, batch_size=64, shuffle=False)

    model = HousePricePredictor()
    criterion = nn.MSELoss()
    optimizer = optim.SGD(model.parameters(), lr=0.001, momentum=0.9)

    epochs = 500
    loss_values = train_model(model, train_loader, criterion, optimizer, epochs)

    # 绘制迭代曲线
    plt.figure()
    plt.plot(range(1, len(loss_values) + 1), loss_values, marker='o',markersize=4)
    plt.xlabel('迭代次数')
    plt.ylabel('损失值')
    plt.title('BP迭代曲线')
    plt.show()

    y_true, y_pred = evaluate_model(model, test_loader, criterion)

    # 绘制实际值和预测值
    plt.figure(figsize=(12, 6))
    plt.plot(y_true, label='实际值', color='blue', marker="o", linewidth=2, markersize=4)
    plt.plot(y_pred, label='预测值', color='red', marker="o", linewidth=2, markersize=4)
    plt.xlabel('样本索引', fontsize=14)
    plt.ylabel('房价', fontsize=14)
    plt.legend(fontsize=14)
    plt.title('实际值和预测值对比', fontsize=16)
    plt.grid(True, which='both', linestyle='--', linewidth=0.5)
    plt.xticks(fontsize=12)
    plt.yticks(fontsize=12)
    plt.show()
