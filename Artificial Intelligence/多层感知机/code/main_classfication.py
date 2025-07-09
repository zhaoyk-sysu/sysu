import torch
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import Dataset, DataLoader
from torchvision import transforms
from PIL import Image
import os
from torch.optim.lr_scheduler import StepLR
import matplotlib.pyplot as plt


# 自定义数据集类
class MNISTDataset(Dataset):
    def __init__(self, root_dir, dataset_type, transform=None):
        self.root_dir = root_dir
        self.transform = transform
        self.img_paths = []
        self.labels = []

        # 遍历文件夹，读取所有的图片
        for filename in os.listdir(root_dir):
            if filename.endswith('.jpg'):
                parts = filename.split('_')
                if parts[0] == dataset_type:
                    label = int(parts[-1].split('.')[0])  # 从文件名提取标签
                    self.img_paths.append(os.path.join(root_dir, filename))
                    self.labels.append(label)

    def __len__(self):
        return len(self.img_paths)

    def __getitem__(self, idx):
        img_path = self.img_paths[idx]
        label = self.labels[idx]
        img = Image.open(img_path)

        # 数据预处理
        if self.transform:
            img = self.transform(img)

        return img, label


# 定义MLP模型
class MLP(nn.Module):
    def __init__(self, input_size, hidden_size, output_size):
        super(MLP, self).__init__()
        self.fc1 = nn.Linear(input_size, hidden_size)
        self.fc2 = nn.Linear(hidden_size, output_size)
        self.relu = nn.ReLU()
        self.softmax = nn.Softmax(dim=1)

    def forward(self, x):
        x = self.relu(self.fc1(x))
        x = self.fc2(x)
        return x


# 超参数设置
input_size = 28 * 28  # 每张图片的像素数（28x28）
hidden_size = 128  # 隐藏层大小
output_size = 10  # 输出为10类数字（0-9）
batch_size = 128
epochs = 10
learning_rate = 0.001

# 数据预处理
transform = transforms.Compose([
    transforms.ToTensor(),
    transforms.Normalize((0.5,), (0.5,))  # 归一化
])

# 数据集根目录
root_dir = r"D:\大二下\人工智能资料\实验课\lab_7_pytorch和MLP\mnist_jpg"

# 加载训练数据集
train_dataset = MNISTDataset(root_dir=root_dir, dataset_type='training', transform=transform)
train_loader = DataLoader(train_dataset, batch_size=batch_size, shuffle=True)

# 加载测试数据集
test_dataset = MNISTDataset(root_dir=root_dir, dataset_type='test', transform=transform)
test_loader = DataLoader(test_dataset, batch_size=batch_size, shuffle=False)

# 直接使用GPU
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

# 初始化模型并移动到GPU
model = MLP(input_size=input_size, hidden_size=hidden_size, output_size=output_size).to(device)

# 损失函数和优化器
criterion = nn.CrossEntropyLoss()
optimizer = optim.Adam(model.parameters(), lr=learning_rate)

# 学习率调度器
scheduler = StepLR(optimizer, step_size=3, gamma=0.1)

# 用于记录每个epoch的损失和准确率
train_losses = []
train_accuracies = []
test_losses = []
test_accuracies = []

# 训练模型
if __name__ == "__main__":
    for epoch in range(epochs):
        model.train()
        running_loss = 0.0
        correct = 0
        total = 0

        for inputs, labels in train_loader:
            inputs = inputs.view(-1, 28 * 28).to(device)  # 扁平化28x28的图片为一维向量并移动到GPU
            labels = labels.to(device)

            # 前向传播
            outputs = model(inputs)
            loss = criterion(outputs, labels)

            # 反向传播
            optimizer.zero_grad()
            loss.backward()
            optimizer.step()

            # 统计损失和准确率
            running_loss += loss.item()
            _, predicted = torch.max(outputs, 1)
            total += labels.size(0)
            correct += (predicted == labels).sum().item()

        # 计算每个epoch的训练损失和准确率
        epoch_train_loss = running_loss / len(train_loader)
        train_accuracy = 100 * correct / total
        train_losses.append(epoch_train_loss)
        train_accuracies.append(train_accuracy)

        # 测试模型
        model.eval()
        running_test_loss = 0.0
        test_correct = 0
        test_total = 0
        with torch.no_grad():
            for test_inputs, test_labels in test_loader:
                test_inputs = test_inputs.view(-1, 28 * 28).to(device)
                test_labels = test_labels.to(device)

                test_outputs = model(test_inputs)
                test_loss = criterion(test_outputs, test_labels)
                running_test_loss += test_loss.item()

                _, test_predicted = torch.max(test_outputs, 1)
                test_total += test_labels.size(0)
                test_correct += (test_predicted == test_labels).sum().item()

        # 计算每个epoch的测试损失和准确率
        epoch_test_loss = running_test_loss / len(test_loader)
        test_accuracy = 100 * test_correct / test_total
        test_losses.append(epoch_test_loss)
        test_accuracies.append(test_accuracy)

        # 更新学习率
        scheduler.step()

        # 打印每个epoch的损失和准确率
        print(f'Epoch [{epoch + 1}/{epochs}], '
              f'Train Loss: {epoch_train_loss:.4f}, Train Accuracy: {train_accuracy:.2f}%, '
              f'Test Loss: {epoch_test_loss:.4f}, Test Accuracy: {test_accuracy:.2f}%')

    # 可视化训练损失和测试损失
    plt.figure(figsize=(10, 5))
    plt.subplot(1, 2, 1)
    plt.plot(train_losses, label='Training Loss')
    plt.plot(test_losses, label='Testing Loss')
    plt.xlabel('Epoch')
    plt.ylabel('Loss')
    plt.legend()

    # 可视化训练准确率和测试准确率
    plt.subplot(1, 2, 2)
    plt.plot(train_accuracies, label='Training Accuracy')
    plt.plot(test_accuracies, label='Testing Accuracy')
    plt.xlabel('Epoch')
    plt.ylabel('Accuracy (%)')
    plt.legend()

    plt.tight_layout()
    plt.show()