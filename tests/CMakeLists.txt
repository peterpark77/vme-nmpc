macro (create_test target)
  add_test (NAME ${target} COMMAND $<TARGET_FILE:${target}>)
endmacro (create_test)

# set(testname ObstacleContainerTest)
# add_executable (${testname} ${testname}.cpp)
# target_link_libraries (${testname} Obstacle)
# create_test(${testname})

# set(testname VirtualMeModelTest)
# add_executable (${testname} ${testname}.cpp)
# target_link_libraries (${testname} VirtualMeNmpcEngine Obstacle)
# create_test(${testname})

set(testname VirtualMeNmpcEngineTest)
add_executable (${testname} ${testname}.cpp FakeVirtualMeModel.cpp
                                            FakeVirtualMeMinimizer.cpp
                                            ../src/Nav2Robot.cpp)
target_link_libraries (${testname} VirtualMeNmpcEngine Obstacle)
create_test(${testname})

#set(testname PathPlannerTest)
#add_executable (${testname} ${testname}.cpp)
#target_link_libraries (${testname} VirtualMeNmpcEngine Obstacle)
#create_test(${testname})