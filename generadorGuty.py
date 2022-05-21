from random import randint

def put_space_or_tree():
    return '*' if randint(0,1000) < 32 else '.'
    
def main():
    n,m = 1000,1000
    with open('maximum_building_1GUTY.in', 'w') as input_generated:
        input_generated.write("{} {}\n".format(n,m))
        for i in range(n):
            input_generated.write(''.join(put_space_or_tree() for _ in range(m)) + '\n')

if __name__ == '__main__':
    main()
