import sqlite3


def get_person_first_name(person_id):
    person = sqlite3.connect("person.db")
    person_cur = person.cursor()
    sqlite_select_query = """SELECT * from person"""
    person_cur.execute(sqlite_select_query)
    person_rows = person_cur.fetchmany(person_id)
    person.close()
    return person_rows[0][1]


def get_person_second_name(person_id):
    person = sqlite3.connect("person.db")
    person_cur = person.cursor()
    sqlite_select_query = """SELECT * from person"""
    person_cur.execute(sqlite_select_query)
    person_rows = person_cur.fetchmany(person_id)
    person.close()
    return person_rows[0][2]


def get_person_passport(person_id):
    person = sqlite3.connect("person.db")
    person_cur = person.cursor()
    sqlite_select_query = """SELECT * from person"""
    person_cur.execute(sqlite_select_query)
    person_rows = person_cur.fetchmany(person_id)
    person.close()
    return person_rows[0][3]


def get_person_address(person_id):
    person = sqlite3.connect("person.db")
    person_cur = person.cursor()
    sqlite_select_query = """SELECT * from person"""
    person_cur.execute(sqlite_select_query)
    person_rows = person_cur.fetchmany(person_id)
    return person_rows[0][4]


def get_person_verification(person_id):
    person = sqlite3.connect("person.db")
    person_cur = person.cursor()
    sqlite_select_query = """SELECT * from person"""
    person_cur.execute(sqlite_select_query)
    person_rows = person_cur.fetchmany(person_id)
    return person_rows[0][5]


def get_bill_kind(person_id):
    bill = sqlite3.connect("bill.db")
    bill_cur = bill.cursor()
    sqlite_select_query = """SELECT * from person"""
    bill_cur.execute(sqlite_select_query)
    bill_rows = bill_cur.fetchmany(person_id)
    bill.close()
    return bill_rows[0][2]


def new_person_create(person_id, first_name, second_name, passport, address, verification):
    try:
        person = sqlite3.connect("person.db")
        person_cur = person.cursor()
        person_module = [person_id, first_name, second_name, passport, address, verification]
        person_cur.execute("INSERT INTO person VALUES("
                           "?, ?, ?, ?, ?, ?);", person_module)
        person.commit()
        person_id += 1  # static ++?
        person_cur.close()

    except sqlite3.Error as error:
        print("Error when working with SQLite", error)
    finally:
        if person:
            person.close()


def new_person_bill_create(person_id, bill_id, bill_kind):
    try:
        bill = sqlite3.connect("bill.db")
        bill_cur = bill.cursor()
        bill_module = [person_id, bill_id, bill_kind]
        bill_cur.execute("INSERT INTO bill VALUES("
                         "?, ?, ?);", bill_module)
        bill.commit()
        bill_id += 1  # static ++?
        bill_cur.close()

    except sqlite3.Error as error:
        print("Error when working with SQLite", error)
    finally:
        if bill:
            bill.close()
