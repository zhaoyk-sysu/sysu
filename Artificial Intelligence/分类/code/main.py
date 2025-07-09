import os
import torch
from torch.utils.data import Dataset, DataLoader
from torchvision import transforms
from PIL import Image
import matplotlib.pyplot as plt
import numpy as np
import torch.nn as nn
from torch.optim.lr_scheduler import StepLR  

# -------------------- 参数设置 --------------------
torch.manual_seed(42)
EPOCH = 30
LR = 0.001
BATCH_SIZE = 32
classes_name = ['baihe', 'dangshen', 'gouqi', 'huaihua', 'jinyinhua']
num_classes = len(classes_name)

# -------------------- 数据增强与预处理 --------------------
train_transform = transforms.Compose([
    transforms.Resize((224, 224)),
    transforms.RandomHorizontalFlip(),
    transforms.RandomRotation(10),
    transforms.ColorJitter(brightness=0.2, contrast=0.2, saturation=0.2),
    transforms.ToTensor(),
    transforms.Normalize([0.485, 0.456, 0.406],
                         [0.229, 0.224, 0.225])
])

test_transform = transforms.Compose([
    transforms.Resize((224, 224)),
    transforms.ToTensor(),
    transforms.Normalize([0.485, 0.456, 0.406],
                         [0.229, 0.224, 0.225])
])

# -------------------- Dataset --------------------
class TCMTrainDataset(Dataset):
    def __init__(self, root_dir, transform):
        self.images = []
        self.labels = []
        self.transform = transform
        for label, class_name in enumerate(classes_name):
            class_dir = os.path.join(root_dir, class_name)
            for img_name in os.listdir(class_dir):
                img_path = os.path.join(class_dir, img_name)
                self.images.append(img_path)
                self.labels.append(label)

    def __len__(self):
        return len(self.images)

    def __getitem__(self, idx):
        image = Image.open(self.images[idx]).convert("RGB")
        image = self.transform(image)
        label = self.labels[idx]
        return image, label

class TCMTestDataset(Dataset):
    def __init__(self, root_dir, transform):
        self.images = []
        self.labels = []
        self.transform = transform
        for label, class_name in enumerate(classes_name):
            class_dir = os.path.join(root_dir, class_name)
            for img_name in os.listdir(class_dir):
                img_path = os.path.join(class_dir, img_name)
                self.images.append(img_path)
                self.labels.append(label)

    def __len__(self):
        return len(self.images)

    def __getitem__(self, idx):
        image = Image.open(self.images[idx]).convert("RGB")
        image = self.transform(image)
        label = self.labels[idx]
        return image, label

# -------------------- 数据加载器 --------------------
train_dataset = TCMTrainDataset(r"C:\Users\19438\Desktop\data\data\tcm\train", transform=train_transform)
test_dataset = TCMTestDataset(r"C:\Users\19438\Desktop\data\data\tcm\test", transform=test_transform)

train_loader = DataLoader(train_dataset, batch_size=BATCH_SIZE, shuffle=True)
test_loader = DataLoader(test_dataset, batch_size=BATCH_SIZE, shuffle=False)

# -------------------- 模型定义 --------------------
class TCM_CNN(nn.Module):
    def __init__(self):
        super(TCM_CNN, self).__init__()
        self.conv = nn.Sequential(
            nn.Conv2d(3, 16, kernel_size=3, padding=1),
            nn.ReLU(),
            nn.MaxPool2d(2),
            nn.Conv2d(16, 32, kernel_size=3, padding=1),
            nn.ReLU(),
            nn.MaxPool2d(2),
            nn.Conv2d(32, 64, kernel_size=3, padding=1),
            nn.ReLU(),
            nn.MaxPool2d(2),
            nn.Conv2d(64, 128, kernel_size=3, padding=1),
            nn.ReLU(),
            nn.MaxPool2d(2)
        )
        self.fc = nn.Sequential(
            nn.Flatten(),
            nn.Linear(128 * 14 * 14, 256),
            nn.ReLU(),
            nn.Dropout(0.5),
            nn.Linear(256, num_classes)
        )

    def forward(self, x):
        x = self.conv(x)
        x = self.fc(x)
        return x

cnn = TCM_CNN()
optimizer = torch.optim.Adam(cnn.parameters(), lr=LR)
loss_func = nn.CrossEntropyLoss()

# 学习率调度器
scheduler = StepLR(optimizer, step_size=6, gamma=0.5)

# -------------------- 训练与测试 --------------------
train_loss_list, train_acc_list, test_acc_list = [], [], []

for epoch in range(EPOCH):
    cnn.train()
    total_loss = 0
    total_correct = 0
    total_samples = 0

    for step, (b_x, b_y) in enumerate(train_loader):
        output = cnn(b_x)
        loss = loss_func(output, torch.tensor(b_y))

        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        total_loss += loss.item()
        pred_y = torch.max(output, 1)[1]
        total_correct += (pred_y == torch.tensor(b_y)).sum().item()
        total_samples += len(b_y)

        if step % 5 == 0:
            print(f"Epoch [{epoch+1}], Step [{step}], Loss: {loss.item():.4f}")

    train_acc = total_correct / total_samples
    train_loss_list.append(total_loss)
    train_acc_list.append(train_acc)

    # ----- 测试 -----
    cnn.eval()
    test_correct = 0
    test_total = 0
    with torch.no_grad():
        for test_images, test_labels in test_loader:
            outputs = cnn(test_images)
            predicted = torch.max(outputs, 1)[1]
            test_total += len(test_labels)
            test_correct += (predicted == torch.tensor(test_labels)).sum().item()

    test_acc = test_correct / test_total
    test_acc_list.append(test_acc)

    # 调整学习率
    scheduler.step()

    current_lr = optimizer.param_groups[0]['lr']
    print(f"Epoch [{epoch+1}] | Train Loss: {total_loss:.4f} | Train Acc: {train_acc:.4f} | Test Acc: {test_acc:.4f} | LR: {current_lr:.6f}")

# -------------------- 可视化 --------------------
plt.figure(figsize=(12, 5))

plt.subplot(1, 2, 1)
plt.plot(range(1, EPOCH + 1), train_loss_list, marker='o', color='red')
plt.title("Train Loss per Epoch")
plt.xlabel("Epoch")
plt.ylabel("Loss")

plt.subplot(1, 2, 2)
plt.plot(range(1, EPOCH + 1), train_acc_list, label='Train Acc', marker='o')
plt.plot(range(1, EPOCH + 1), test_acc_list, label='Test Acc', marker='s')
plt.title("Accuracy per Epoch")
plt.xlabel("Epoch")
plt.ylabel("Accuracy")
plt.legend()

plt.tight_layout()
plt.show()
