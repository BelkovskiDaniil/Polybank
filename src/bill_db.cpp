#include "include/bill_db.h"

bill_db::bill_db(char* err, sqlite3* bill_db) : err_(err), bill_db_(bill_db) {
  sqlite3_open("myDb.db", &bill_db_);

  std::string query = "CREATE TABLE IF NOT EXISTS bill("
                      "person_id varchar(10) PRIMARY KEY, "
                      "bill_id varchar(10), "
                      "bill_kind varchar(10), "
                      "cash_size varchar(10));";

  auto bill = sqlite3_exec(bill_db_, query.c_str(), NULL, NULL, &err_);
  if (bill != SQLITE_OK) {
    throw std::string("Database error: " + std::string(err_));
  }
}

void bill_db::create_bill_query(ibill* person_bill) {
  std::string bill_query = "INSERT INTO bill VALUES('" + person_bill->get_person_id().toString() + "', '"
      + person_bill->get_bill_id().toString() + "', '" + person_bill->get_bill_kind() + "', '"
      + person_bill->get_cash_size().toString() + "');";
  std::cout << bill_query << "\n";
  auto bill = sqlite3_exec(bill_db_, bill_query.c_str(), NULL, NULL, &err_);

  if (bill != SQLITE_OK) {
    throw std::string("Database error: " + std::string(err_));
  }
}

ibill* bill_db::bill_find(const big_int& bill_id) {
  std::string bill_query = "SELECT * FROM bill WHERE bill_id = ? LIMIT 1;";
  sqlite3_stmt* stmt;

  int rc = sqlite3_prepare_v2(bill_db_, bill_query.c_str(), -1, &stmt, nullptr);

  if (rc != SQLITE_OK) {
    sqlite3_close(bill_db_);
    throw std::string("Fuck u asshole ");
  }

  rc = sqlite3_bind_text(stmt, 1, bill_id.toString().c_str(), -1, SQLITE_TRANSIENT);

  if (sqlite3_step(stmt) == SQLITE_ROW) {
    big_int person_id(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
    std::string bill_kind = (reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
    const char* a = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
    big_int cash_size(a);
    std::cout << "Person id: " << person_id << " Bill id: " << bill_id << " Bill kind: " << bill_kind << " Cash size: "
              << cash_size << std::endl;

    sqlite3_finalize(stmt);
    bill_factory factory;
    if (bill_kind == BILL_KIND_CREDIT) {
      return factory.build_credit(person_id);
    } else if (bill_kind == BILL_KIND_DEBIT) {
      return factory.build_debit(person_id);
    } else if (bill_kind == BILL_KIND_DEPOSIT) {
      return factory.build_deposit(person_id);
    }

  } else {
    throw std::string("Fuck u asshole can`t find bill");
  }
  return nullptr;
}

ibill* bill_db::bill_delete_and_find(const big_int& bill_id) {
  std::string bill_query = "SELECT * FROM bill WHERE bill_id = ? LIMIT 1;";
  sqlite3_stmt* stmt;

  int rc = sqlite3_prepare_v2(bill_db_, bill_query.c_str(), -1, &stmt, nullptr);

  if (rc != SQLITE_OK) {
    sqlite3_close(bill_db_);
    throw std::string("Fuck u asshole ");
  }

  rc = sqlite3_bind_text(stmt, 1, bill_id.toString().c_str(), -1, SQLITE_TRANSIENT);

  if (sqlite3_step(stmt) == SQLITE_ROW) {
    big_int person_id(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
    std::string bill_kind = (reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
    const char* a = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
    big_int cash_size(a);
    std::cout << "Person id: " << person_id << " Bill id: " << bill_id << " Bill kind: " << bill_kind << " Cash size: "
              << cash_size << std::endl;

    std::string delete_query = "DELETE FROM bill WHERE bill_id = ? LIMIT 1;";

    rc = sqlite3_prepare_v2(bill_db_, delete_query.c_str(), -1, &stmt, nullptr);

      if (rc != SQLITE_OK) {
          sqlite3_close(bill_db_);
          throw std::string("Fuck u asshole ");
      }

      rc = sqlite3_bind_text(stmt, 1, bill_id.toString().c_str(), -1, SQLITE_TRANSIENT);


    sqlite3_finalize(stmt);
    bill_factory factory;
    if (bill_kind == BILL_KIND_CREDIT) {
      return factory.build_credit(person_id);
    } else if (bill_kind == BILL_KIND_DEBIT) {
      return factory.build_debit(person_id);
    } else if (bill_kind == BILL_KIND_DEPOSIT) {
      return factory.build_deposit(person_id);
    }

  } else {
    throw std::string("Fuck u asshole can`t find bill");
  }
  return nullptr;
}

bill_db::~bill_db() {
  sqlite3_close(bill_db_);
}