# Лабораторная работа №3
Срок выполнения работы: с 2022-09-30 по 2022-10-06.
Срок сдачи работы: 2022-10-07.

## Основы работы с библиотекой Qt

### Ответвление
Необходимо создать ответвление (fork) моего репозитория Lab-03 (название 
оставить без изменения, а видимость поставить приватной). Назничить меня в 
новом репозитории соавтором с правами администратора. Вики, Задачи а также
Проекты отключить.

В локальной копии создавать ветки (branch) по необходимости.

### Этап разработки
Доработать программу "Текстовый редактор" из задания лабораторной работы 2
следующим образом:
  * Добавить пункт главного меню "Инструменты"
  * В меню "Инструменты" добавить пункт "Граф вызовов" - создающий новое 
    окно в котором строится граф вызовов для текущей вкладки "Редактора".
    Для построения графа вызовов использовать QGraphicsScene. 
    Если текущая вкладка не открыта либо пуста, пункт меню недоступен.
    Информацию, необходимую для построения графа вызовов, получить с помощью 
    cflow.

По разработанной программе подготовить отчет в соответствии с требованиями 
ГОСТ 19. Отчет в обязательном порядке должен содержать диаграмму классов 
в формате UML-2.0. Отчет включить в состав исходных коддов программы в виде
файла формата PDF.

### Запрос слияния
По итогу выполнения работы создать запрос на слияние (pull request) 
и назначить меня рецензентом.

