# VTune DuckDB Example

This example demonstrates how to profile DuckDB with Intel® VTune.

## Building

1. Ensure you have [CMake](https://cmake.org) installed (minimum version 3.14).
	```
	cmake --version
	```
2. From the project's root directory, create and navigate into a build directory.
	```
	mkdir build && cd build
	```
3. Configure and build the project.
	```
	cmake .. -DCMAKE_BUILD_TYPE=Release
	cmake --build . --parallel
	```
4. Run the executable. If this works, proceed to the next section.
	```
	./vtune_duckdb_example
	```

## Profiling

1. Ensure you have [Intel® VTune](https://www.intel.com/content/www/us/en/developer/tools/oneapi/vtune-profiler.html) installed.
2. Run a predefined analysis, if desired. For example, analyze hotspots.
	```
	vtune -collect performance-snapshot ./vtune_duckdb_example
	```
3. Run a custom analysis, if desired. For example, count instructions retired and execution stalls. You may need to search for the [performance counter events](https://perfmon-events.intel.com) specific to your system.
	```
	vtune \
		-collect-with runsa \
		-knob event-config=INST_RETIRED.ANY,CYCLE_ACTIVITY.STALLS_TOTAL \
		./vtune_duckdb_example
	```
4. Output the results to a CSV file. For example, output the result from the analysis above.
	```
	vtune -report hw-events \
		-r <result_directory> \
		-group-by frame-domain \
		-report-output result.csv \
		-format csv \
		-csv-delimiter comma
	```
