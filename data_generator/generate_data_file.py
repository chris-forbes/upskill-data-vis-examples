import random
from math import ceil


def current_percentage(current_count:int, max_len:int) -> int:
    return ceil( (current_count / max_len) * 100 )

def percentage_chance(chance: int)->bool:
    return random.randint(0,100) < chance


if __name__ == '__main__':
    max_len = 1000000
    percent_chance = 12
    common = ['cat','dog', 'fish','hamster']
    uncommon = ['parrot', 'fox', 'turtle', 'gecko', 'ferret','horse','budgie', 'pig', 'zebra']
    with open('data_file.txt', 'w') as output_file:
        for i in range(0, max_len):
            print(f"writing line {i + 1} of {max_len}, percentage complete: {current_percentage(i, max_len)}%", end='\r')
            if percentage_chance(percent_chance):
                output_file.write(random.choice(uncommon)+'\n')
                continue
            else:
                output_file.write(random.choice(common) + '\n')
    print('Done')
