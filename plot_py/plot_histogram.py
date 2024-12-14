import matplotlib.pyplot as plt
import sys
import argparse

def read_scores_from_file(filename):
    """从文件读取成绩数据"""
    scores = []
    with open(filename, 'r') as f:
        for line in f:
            try:
                score = int(line.strip())
                if 0 <= score <= 100:
                    scores.append(score)
            except ValueError:
                continue
    return scores

def plot_histogram(scores):
    """绘制成绩分布直方图"""
    # 设置中文字体
    plt.rcParams['font.family'] = ['SimHei']
    plt.rcParams['axes.unicode_minus'] = False
    
    # 创建新的图形
    plt.figure(figsize=(10, 6))
    
    # 设置直方图的区间
    bins = range(0, 105, 5)  # 0-100分，步长为5
    
    # 绘制直方图
    n, bins, patches = plt.hist(scores, bins=bins, edgecolor='black', alpha=0.7)
    
    # 在每个柱子上方添加频数标签
    for i in range(len(n)):
        if n[i] > 0:  # 只在有数据的柱子上添加标签
            plt.text(bins[i] + 2.5, n[i], int(n[i]), 
                    ha='center', va='bottom')
    
    # 设置标题和标签
    plt.title('学生成绩分布')
    plt.xlabel('成绩区间')
    plt.ylabel('学生人数')
    
    # 添加网格
    plt.grid(True, alpha=0.3)
    
    # 设置x轴范围和刻度
    plt.xlim(-5, 105)
    plt.xticks(range(0, 101, 10))
    
    # 显示图形
    plt.show(block=True)

if __name__ == "__main__":
    # 设置命令行参数
    parser = argparse.ArgumentParser(description='绘制成绩分布直方图')
    parser.add_argument('-f', '--file', required=True, help='成绩数据文件路径')
    args = parser.parse_args()
    
    try:
        # 从文件读取成绩数据
        scores = read_scores_from_file(args.file)
        
        if not scores:
            print("没有有效的成绩数据！")
            sys.exit(1)
        
        # 打印成绩统计信息
        print(f"\n=== 成绩统计 ===")
        print(f"有效数据数量: {len(scores)}")
        print(f"最高分: {max(scores)}")
        print(f"最低分: {min(scores)}")
        print(f"平均分: {sum(scores) / len(scores):.2f}")
        
        # 绘制直方图
        plot_histogram(scores)
        
    except Exception as e:
        print(f"发生错误: {e}")
        sys.exit(1)