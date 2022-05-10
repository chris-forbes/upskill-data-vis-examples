import pandas as pd
import sys

def load_file(file: str) -> pd.DataFrame:
    return pd.read_csv(file, header=None)

def calculate_distribution(row, total):
    return (row['counts'] / total) *100

def coerce_series_to_dataframe(key:str, series: pd.Series) -> pd.DataFrame:
    return pd.DataFrame({key : series})

def group_and_count_initial_dataset(dataframe: pd.DataFrame) -> pd.Series:
    return dataframe.value_counts()

if __name__ == '__main__':
    if len(sys.argv) <= 1:
        print('''
        Failed to read file, please specify an input file
        Usage:
            python3 pandas_example.py <file to read>
        ''')
        sys.exit(-1)
    _data_df = load_file(str(sys.argv[1]))
    animal_frame = coerce_series_to_dataframe('counts', group_and_count_initial_dataset(_data_df))
    total = group_and_count_initial_dataset(_data_df).sum()
    print(f"Total number is: {total}")
    animal_frame['distribution'] = animal_frame.apply(lambda x: calculate_distribution(x, total), axis=1)
    print(animal_frame)
    max_row = animal_frame.query('counts == counts.max()')
    min_row = animal_frame.query('counts == counts.min()')
    print(f"Max row is: {max_row}")
    print(f"Min row is: {min_row}")
