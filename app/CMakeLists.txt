cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr)
project(my_zephyr_app)


target_sources(app PRIVATE src/main.c src/scheduler.c src/scheduler_runnables.c)
target_include_directories(app PUBLIC inc/)
