import pandas as pd

def xlsx_to_csv(xlsx_file, csv_file):
    # 读取 Excel 文件
    df = pd.read_excel(xlsx_file)
    
    # 将数据写入 CSV 文件
    df.to_csv(csv_file, index=False, encoding='gbk')

# 调用函数
xlsx_to_csv('../data/student_scores.xlsx', '../data/student_scores.csv')