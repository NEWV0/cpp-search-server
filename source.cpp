#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>
 
using namespace std;
 
// Перечислимый тип для статуса задачи
enum class TaskStatus {
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};
 
// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;
 
class TeamTasks {
public:
    const TasksInfo& GetPersonTasksInfo(const string& person) const {
        return tasks.at(person);
    }
 
    void AddNewTask(const string& person) {
        tasks[person][TaskStatus::NEW]++;
    }
 
tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {
    TasksInfo updated_tasks, untouched_tasks;
 
    if (tasks.find(person) == tasks.end()) {
        return make_tuple(updated_tasks, untouched_tasks);
    }
 
    TasksInfo& person_tasks = tasks[person];
 
    for (auto status : { TaskStatus::NEW, TaskStatus::IN_PROGRESS, TaskStatus::TESTING }) {
        if (task_count == 0) {
            break;
        }
 
        if (person_tasks[status] > 0) {
            int tasks_to_update = min(task_count, person_tasks[status]);
            task_count -= tasks_to_update;
 
            TaskStatus next_status = GetNextStatus(status);
            person_tasks[status] -= tasks_to_update;
            person_tasks[next_status] += tasks_to_update;
 
 
            updated_tasks[next_status] += tasks_to_update;
        }
    }
 
    TasksInfo remaining_tasks = person_tasks;
    for (auto [status, count] : updated_tasks) {
        remaining_tasks[status] -= count;
    }
 
    for (auto [status, count] : remaining_tasks) {
        if (status != TaskStatus::DONE && count > 0) {
            untouched_tasks[status] = count;
        }
    }
 
    return tuple(updated_tasks, untouched_tasks);
}
 
private:
    map<string, TasksInfo> tasks;
 
    TaskStatus GetNextStatus(TaskStatus status) const {
        switch (status) {
        case TaskStatus::NEW:
            return TaskStatus::IN_PROGRESS;
        case TaskStatus::IN_PROGRESS:
            return TaskStatus::TESTING;
        case TaskStatus::TESTING:
            return TaskStatus::DONE;
        default:
            return TaskStatus::DONE; 
        }
    }
};
 
// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks"s
        << ", "s << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress"s
        << ", "s << tasks_info[TaskStatus::TESTING] << " tasks are being tested"s
        << ", "s << tasks_info[TaskStatus::DONE] << " tasks are done"s << endl;
}
 
int main() {
    TeamTasks tasks;
    tasks.AddNewTask("Ilia"s);
    for (int i = 0; i < 3; ++i) {
        tasks.AddNewTask("Ivan"s);
    }
    cout << "Ilia's tasks: "s;
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"s));
    cout << "Ivan's tasks: "s;
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"s));
 
    TasksInfo updated_tasks, untouched_tasks;
 
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan"s, 2);
    cout << "Updated Ivan's tasks: "s;
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: "s;
    PrintTasksInfo(untouched_tasks);
 
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan"s, 2);
    cout << "Updated Ivan's tasks: "s;
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: "s;
    PrintTasksInfo(untouched_tasks);
} 