import psycopg2


if __name__ == '__main__':
    print('loading data from ../data/data_file.txt')
    try:
        conn = psycopg2.connect("dbname='test' user='postgres' host='localhost' password='password'")
        with open('../data/data_file.txt', 'r') as inf:
            cur = conn.cursor()
            for line in inf:
                line = str(line).replace('\n','')
                sql = f"insert into pets (animal) values ('{line}')"
                print(f"Executing {sql}")
                cur.execute(sql)
        conn.commit()
    except:
            print ("I am unable to connect to the database")
