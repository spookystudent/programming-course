import matplotlib.pyplot as plt
import pandas as pd
import numpy as np


class Graphics:
    filename = ''

    def __init__(self, filename):
        self.filename = filename

        try:
            with open(filename, 'r') as f:
                print(f'Файл найден: {filename}')
        except FileNotFoundError:
            raise FileExistsError(f"Ошибка: файл {filename} не найден")



    def read_data(self, filename=None):
        data = []
        if filename is None:
            filename = self.filename
        
        with open(filename, 'r') as f:
            for line in f:
                line = line.strip()
                if not line:
                    continue
                if line.count(',') == 3:
                    variety, max_rows, without_idx, with_idx = map(float, line.split(','))
                    data.append({
                        'variety': int(variety),
                        'max_rows': int(max_rows),
                        'without_idx': without_idx,
                        'with_idx': with_idx
                    })
        return pd.DataFrame(data)
    


    def show(self, data):
        varieties = data['variety'].unique()
        
        fig, axes = plt.subplots(len(varieties), 1, figsize=(12, 8), sharex=True)
        if len(varieties) == 1:
            axes = [axes]
        
        for i, variety in enumerate(varieties):
            ax = axes[i]
            subset = data[data['variety'] == variety]
            
            ax.plot(subset['max_rows'], subset['without_idx'], 'r-', label='Без индекса', marker='o')
            ax.plot(subset['max_rows'], subset['with_idx'], 'b-', label='С индексом', marker='s')
            
            ax.set_title(f'Variety = {int(variety)}')
            ax.set_ylabel('Время (мкс)')
            ax.grid(True, which="both", ls="-")
            ax.legend()
        
        plt.xlabel('Количество строк')
        plt.suptitle('Сравнение времени выполнения SELECT запроса с индексом и без', y=1.02)
        plt.tight_layout()
        plt.show()


if __name__ == "__main__":
    manager = Graphics(filename="C:/UserFiles/git/@spookystudent/programming-course/2.2/laba-3/data.txt")

    manager.show(
        data=manager.read_data()
    )