  // Copyright 2024 Lee V.

#include <iostream>

#include "Deanery.h"

int main() {
    // создаем деканат с файлами "groups.txt" для групп
    // и "students.txt" для студентов
    Deanery deanery("groups.txt", "students.txt");

    // выбираем старост для групп
    deanery.initHeads();

    // выводим статистику
    deanery.printStatistics();

    // добавляем всем студентам по 2 случайных оценки
    deanery.addMarksToAll(2);

    // проводим отчисление студентов с плохой успеваемостью
    deanery.fireStudents();

    // проводим перевод студентов
    deanery.moveStudent("Варакин Владислав Дмитриевич", "23КНТ5");
    deanery.moveStudent("Бычков Илья Сергеевич", "23КНТ6");
    deanery.moveStudent("Акулова Алена Сергеевна", "23КНТ9");
    deanery.moveStudent("Ульянова Ульяна Владимировна", "23КНТ7");

    // выводим статистику (обновленную)
    deanery.printStatistics();

    return 0;
}
