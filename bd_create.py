import sqlite3

per = sqlite3.connect("person.db")
per_cur = per.cursor()
per_cur.execute("CREATE TABLE IF NOT EXISTS person("
                "person_id INT PRIMARY KEY, "
                "first_name TEXT, "
                "second_name TEXT, "
                "passport INT, "
                "address TEXT, "
                "verification INT);")
per.commit()

bill = sqlite3.connect("bill.db")
bill_cur = bill.cursor()
bill_cur.execute("CREATE TABLE IF NOT EXISTS bill("
                 "person_id INT PRIMARY KEY, "
                 "bill_id INT, "
                 "bill_kind TEXT);")
bill.commit()
