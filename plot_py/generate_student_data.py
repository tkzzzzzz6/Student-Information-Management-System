# -*- coding: gbk -*-

import pandas as pd
import os
import random
from datetime import datetime, timedelta

def load_student_data(file_path):
    """��ȡѧ������CSV�ļ�"""
    try:
        df = pd.read_csv(file_path, encoding='gbk')
        return df
    except Exception as e:
        print(f"��ȡ�ļ�ʱ����: {e}")
        return None

def save_student_data(df, output_path):
    """���洦����ѧ������"""
    try:
        df.to_csv(output_path, index=False, encoding='gbk')
        print(f"�����ѱ��浽: {output_path}")
    except Exception as e:
        print(f"�����ļ�ʱ����: {e}")

def generate_random_date(start_year=2003, end_year=2005):
    """���������������"""
    start_date = datetime(start_year, 1, 1)
    end_date = datetime(end_year, 12, 31)
    days_between = (end_date - start_date).days
    random_days = random.randint(0, days_between)
    random_date = start_date + timedelta(days=random_days)
    return random_date.strftime("%Y-%m-%d")

def generate_student_id(year, college_code, count):
    """����ѧ��,����֤ѧ��Ψһ"""
    # ʹ�ü��ϴ洢�����ɵ�ѧ��
    if not hasattr(generate_student_id, 'used_ids'):
        generate_student_id.used_ids = set()
    
    # ������ѧ��
    student_id = f"{year}{college_code:02d}{count:03d}"
    
    # ���ѧ���Ѵ���,����countֱ������Ψһѧ��
    while student_id in generate_student_id.used_ids:
        count += 1
        student_id = f"{year}{college_code:02d}{count:03d}"
    
    # ����ѧ����ӵ���ʹ�ü�����
    generate_student_id.used_ids.add(student_id)
    
    return student_id

def add_student_records(num_records=2000):
    """��������ѧ����¼"""
    # Ԥ������ܵ�ֵ
    colleges = {
        "��Ϣ����ѧԺ": ["�������ѧ�뼼��", "�����ݿ�ѧ�뼼��",  "����������"],
        "������ѧѧԺ": ["�����ѧ", "���＼��", "���﹤��"],
        "����ѧԺ": ["ũҵ��е�������Զ���", "ũҵ������", "ũҵ����"],
        "����ѧԺ": ["��������ѧ", "����ѧ"],
        "��ѧԺ": ["��ѧ��Ӧ����ѧ", "Ӧ������ѧ", "��ѧ","��Ϣ������ѧ","���ﻯѧ"],
        "ũѧԺ": ["ũѧ", "԰��", "ֲ�ﱣ��","ũҵ��Դ�뻷��","ũҵˮ������"],
        "�����봫ýѧԺ": ["����ѧ", "����ѧ", "�赸ѧ","�Ӿ��������","�������"],
        "����ѧԺ": ["��������", "�������ָ�������", "�˶�ѵ��"],
        "���˼����ѧԺ": ["���˼��������", "˼�����ν���", "��ѧ"],
        "ʳƷѧԺ": ["ʳƷ��ѧ�빤��", "ʳƷ�����밲ȫ", "ʳƷӪ���뽡��"],
        "����ҽѧԺ": ["����ҽѧ", "�����ѧ", "����ҩѧ"],
    }
    
    grades = [2021, 2022, 2023,2024]
    genders = ["��", "Ů"]
    
    new_records = []
    college_counters = {college: 1 for college in colleges.keys()}
    
    for _ in range(num_records):
        # ���ѡ��ϵ���רҵ
        college = random.choice(list(colleges.keys()))
        major = random.choice(colleges[college])
        grade = random.choice(grades)
        
        # ���ɰ༶�ţ�1-4��
        class_num = random.randint(1, 4)
        # ����רҵ���ȣ�ȷ���༶�ų���
        if len(major)<5:
            class_name = f"{major[:2]}{grade%100:04d}{class_num:02d}"
        else:
            class_name = f"{major[:3]}{grade%100:04d}{class_num:02d}"
        
        # ����ѧ��
        college_code = list(colleges.keys()).index(college) + 1
        student_id = generate_student_id(grade, college_code, college_counters[college])
        college_counters[college] += 1
        
        # ���ɳɼ���60-100��
        scores = {
            "���޳ɼ�": random.randint(60, 100),
            "ѡ�޳ɼ�": random.randint(60, 100),
            "���γɼ�": random.randint(60, 100),
            "���´�ҵ�ɼ�": random.randint(60, 100)
        }
        
        # ������������ʾ����
        surnames = "��Ǯ��������֣��������������������������ʩ�ſײ��ϻ���κ�ս�½�ֵ�Ƚ���������ܽ�ʯ̷������������"
        names = "ܿ�����ľ�����־������ƽ��������������ΰǿ����÷��"
        name = random.choice(surnames) + random.choice(names)
        if random.random() < 0.3:  # 30%�������������ֵ���
            name += random.choice(names)
            
        record = {
            "ϵ��": college,
            "�꼶": grade,
            "�༶": class_name,
            "ѧ��": student_id,
            "����": name,
            "�Ա�": random.choice(genders),
            "����������": generate_random_date(),
            "רҵ": major,
            "�������": "����",
            "ѧ��": 4,
            "У��": "�Ű�",
            "���޳ɼ�": scores["���޳ɼ�"],
            "ѡ�޳ɼ�": scores["ѡ�޳ɼ�"],
            "���γɼ�": scores["���γɼ�"],
            "���´�ҵ�ɼ�": scores["���´�ҵ�ɼ�"]
        }
        new_records.append(record)
    
    return pd.DataFrame(new_records)

def main():
    # ��ȡԭʼ����
    input_file = "student_scores.csv"
    output_file = "updated_student_scores.csv"
    
    df_original = load_student_data(input_file)
    if df_original is None:
        return
    
    # �����¼�¼
    df_new = add_student_records(10000)  # ����10000���¼�¼
    
    # �ϲ�ԭ�����ݺ�������,����ԭ������
    df_combined = pd.concat([df_original, df_new], ignore_index=True)
    
    # ��ϵ���꼶���༶����
    df_combined = df_combined.sort_values(by=['ϵ��', '�꼶', '�༶', 'ѧ��'])
    
    # ������º������
    save_student_data(df_combined, output_file)
    
    # ��ʾ����ͳ����Ϣ
    print("\n����ͳ����Ϣ:")
    print(f"��ѧ����: {len(df_combined)}")
    print("\n��ϵ��ѧ������:")
    print(df_combined['ϵ��'].value_counts())
    print("\n���꼶ѧ������:")
    print(df_combined['�꼶'].value_counts())
    print("\n��רҵѧ������:")
    print(df_combined['רҵ'].value_counts())
    
    # ��ʾ�ɼ�ͳ����Ϣ
    print("\n�ɼ�ͳ����Ϣ:")
    score_columns = ['���޳ɼ�', 'ѡ�޳ɼ�', '���γɼ�', '���´�ҵ�ɼ�']
    for col in score_columns:
        print(f"\n{col}ͳ��:")
        print(f"ƽ����: {df_combined[col].mean():.2f}")
        print(f"��߷�: {df_combined[col].max()}")
        print(f"��ͷ�: {df_combined[col].min()}")

if __name__ == "__main__":
    main() 