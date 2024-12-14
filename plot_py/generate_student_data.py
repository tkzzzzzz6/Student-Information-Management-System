# -*- coding: gbk -*-

import pandas as pd
import os
import random
from datetime import datetime, timedelta

def load_student_data(file_path):
    """读取学生数据CSV文件"""
    try:
        df = pd.read_csv(file_path, encoding='gbk')
        return df
    except Exception as e:
        print(f"读取文件时出错: {e}")
        return None

def save_student_data(df, output_path):
    """保存处理后的学生数据"""
    try:
        df.to_csv(output_path, index=False, encoding='gbk')
        print(f"数据已保存到: {output_path}")
    except Exception as e:
        print(f"保存文件时出错: {e}")

def generate_random_date(start_year=2003, end_year=2005):
    """生成随机出生日期"""
    start_date = datetime(start_year, 1, 1)
    end_date = datetime(end_year, 12, 31)
    days_between = (end_date - start_date).days
    random_days = random.randint(0, days_between)
    random_date = start_date + timedelta(days=random_days)
    return random_date.strftime("%Y-%m-%d")

def generate_student_id(year, college_code, count):
    """生成学号,并保证学号唯一"""
    # 使用集合存储已生成的学号
    if not hasattr(generate_student_id, 'used_ids'):
        generate_student_id.used_ids = set()
    
    # 生成新学号
    student_id = f"{year}{college_code:02d}{count:03d}"
    
    # 如果学号已存在,增加count直到生成唯一学号
    while student_id in generate_student_id.used_ids:
        count += 1
        student_id = f"{year}{college_code:02d}{count:03d}"
    
    # 将新学号添加到已使用集合中
    generate_student_id.used_ids.add(student_id)
    
    return student_id

def add_student_records(num_records=2000):
    """批量生成学生记录"""
    # 预定义可能的值
    colleges = {
        "信息工程学院": ["计算机科学与技术", "大数据科学与技术",  "物联网工程"],
        "生命科学学院": ["生物科学", "生物技术", "生物工程"],
        "机电学院": ["农业机械化及其自动化", "农业电气化", "农业工程"],
        "人文学院": ["汉语言文学", "新闻学"],
        "理学院": ["数学与应用数学", "应用物理学", "化学","信息与计算科学","生物化学"],
        "农学院": ["农学", "园艺", "植物保护","农业资源与环境","农业水利工程"],
        "艺术与传媒学院": ["音乐学", "美术学", "舞蹈学","视觉传达设计","环境设计"],
        "体育学院": ["体育教育", "社会体育指导与管理", "运动训练"],
        "马克思主义学院": ["马克思主义理论", "思想政治教育", "哲学"],
        "食品学院": ["食品科学与工程", "食品质量与安全", "食品营养与健康"],
        "动物医学院": ["动物医学", "动物科学", "动物药学"],
    }
    
    grades = [2021, 2022, 2023,2024]
    genders = ["男", "女"]
    
    new_records = []
    college_counters = {college: 1 for college in colleges.keys()}
    
    for _ in range(num_records):
        # 随机选择系别和专业
        college = random.choice(list(colleges.keys()))
        major = random.choice(colleges[college])
        grade = random.choice(grades)
        
        # 生成班级号（1-4）
        class_num = random.randint(1, 4)
        # 根据专业长度，确定班级号长度
        if len(major)<5:
            class_name = f"{major[:2]}{grade%100:04d}{class_num:02d}"
        else:
            class_name = f"{major[:3]}{grade%100:04d}{class_num:02d}"
        
        # 生成学号
        college_code = list(colleges.keys()).index(college) + 1
        student_id = generate_student_id(grade, college_code, college_counters[college])
        college_counters[college] += 1
        
        # 生成成绩（60-100）
        scores = {
            "必修成绩": random.randint(60, 100),
            "选修成绩": random.randint(60, 100),
            "二课成绩": random.randint(60, 100),
            "创新创业成绩": random.randint(60, 100)
        }
        
        # 生成姓名（简单示例）
        surnames = "赵钱孙李周吴郑王冯陈褚卫蒋沈韩杨朱秦尤许何吕施张孔曹严华金魏陶姜陆贾邓冉彭阮阮邹熊金石谭凤云忠钟周乐"
        names = "芸娟婷文军明永志国建华平红林玉晓丽静婷伟强齐龙梅磊"
        name = random.choice(surnames) + random.choice(names)
        if random.random() < 0.3:  # 30%概率生成两个字的名
            name += random.choice(names)
            
        record = {
            "系别": college,
            "年级": grade,
            "班级": class_name,
            "学号": student_id,
            "姓名": name,
            "性别": random.choice(genders),
            "出生年月日": generate_random_date(),
            "专业": major,
            "培养层次": "本科",
            "学制": 4,
            "校区": "雅安",
            "必修成绩": scores["必修成绩"],
            "选修成绩": scores["选修成绩"],
            "二课成绩": scores["二课成绩"],
            "创新创业成绩": scores["创新创业成绩"]
        }
        new_records.append(record)
    
    return pd.DataFrame(new_records)

def main():
    # 读取原始数据
    input_file = "student_scores.csv"
    output_file = "updated_student_scores.csv"
    
    df_original = load_student_data(input_file)
    if df_original is None:
        return
    
    # 创建新记录
    df_new = add_student_records(10000)  # 生成10000条新记录
    
    # 合并原有数据和新数据,保留原有数据
    df_combined = pd.concat([df_original, df_new], ignore_index=True)
    
    # 按系别、年级、班级排序
    df_combined = df_combined.sort_values(by=['系别', '年级', '班级', '学号'])
    
    # 保存更新后的数据
    save_student_data(df_combined, output_file)
    
    # 显示数据统计信息
    print("\n数据统计信息:")
    print(f"总学生数: {len(df_combined)}")
    print("\n各系别学生人数:")
    print(df_combined['系别'].value_counts())
    print("\n各年级学生人数:")
    print(df_combined['年级'].value_counts())
    print("\n各专业学生人数:")
    print(df_combined['专业'].value_counts())
    
    # 显示成绩统计信息
    print("\n成绩统计信息:")
    score_columns = ['必修成绩', '选修成绩', '二课成绩', '创新创业成绩']
    for col in score_columns:
        print(f"\n{col}统计:")
        print(f"平均分: {df_combined[col].mean():.2f}")
        print(f"最高分: {df_combined[col].max()}")
        print(f"最低分: {df_combined[col].min()}")

if __name__ == "__main__":
    main() 