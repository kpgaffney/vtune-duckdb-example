#include <iostream>

#include "duckdb.hpp"
#include "ittnotify.h"

int main() {
  duckdb::DuckDB db;
  duckdb::Connection con(db);

  std::cout << "Installing TPC-H extension..." << std::endl;
  con.Query("INSTALL tpch")->Print();

  std::cout << "Loading TPC-H extension..." << std::endl;
  con.Query("LOAD tpch")->Print();

  std::cout << "Generating TPC-H data..." << std::endl;
  con.Query("CALL dbgen(sf=1)")->Print();

  for (int query_number = 1; query_number <= 22; ++query_number) {
    std::string query_name = "Q" + std::to_string(query_number);
    std::cout << "Running TPC-H " << query_name << "..." << std::endl;

    // Create a named domain for the query.
    ___itt_domain *domain = __itt_domain_create(query_name.c_str());

    // Create a frame and run the query.
    __itt_frame_begin_v3(domain, nullptr);
    con.Query("PRAGMA tpch(" + std::to_string(query_number) + ")");
    __itt_frame_end_v3(domain, nullptr);
  }

  return 0;
}
