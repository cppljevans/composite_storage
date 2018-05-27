# Copyright Louis Dionne 2017
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
#=====================
#  The following copied with "slight" modification from:
#    https://github.com/ldionne/metabench/blob/master/benchmark/hetero/find_if/CMakeLists.txt

cmake_minimum_required(VERSION 3.1)

project(Metabench CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${METABENCH_TOP})
include_directories(BEFORE ${CMAKE_INCLUDE_DIRECTORIES})

# Actually include the module
include(metabench)

# Add new datasets
set(benchmark_n_range "(10..50).step(10).to_a + (100..160).step(20).to_a") #for production
#set(benchmark_n_range "(10..20).step(10).to_a") #for testing
metabench_add_dataset(hana.just_find hana.map.just_find.cpp.erb ${benchmark_n_range} ENV "{k: 10}")
#metabench_add_dataset(hana.make_find hana.map.make_find.cpp.erb ${benchmark_n_range} ENV "{k: 10}")
#^Skip above because size overwhelms other graphs.
metabench_add_dataset(MapAsTuple.just_find MapAsTuple.just_find.cpp.erb ${benchmark_n_range} ENV "{k: 10}")
metabench_add_dataset(MapAsTuple.make_find MapAsTuple.make_find.cpp.erb ${benchmark_n_range} ENV "{k: 10}")
unset(benchmark_n_range)

# Add a new chart
metabench_add_chart(chart DATASETS hana.just_find MapAsTuple.just_find MapAsTuple.make_find)
