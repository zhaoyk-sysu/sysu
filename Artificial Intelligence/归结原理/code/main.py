import my_Predicate


def show_menu1():
    print('选择运行案例：')
    print('1：运行案例1')
    print('2：运行案例2')
    print('3：运行案例3')
    print('0：结束程序')


def show_menu2():
    print('1：显示案例内容')
    print('2：输出归结过程')
    print('0：返回，重新选择案例')


if __name__ == '__main__':
    while True:
        show_menu1()
        choice = input('请选择你想实现的案例：')
        print()
        match choice:
            case '1':
                while True:
                    show_menu2()
                    choice2 = input('选择你想实现的功能：')
                    match choice2:
                        case '1':
                            with open('test1.txt', encoding='utf-8') as file_obj:
                                contents = file_obj.read()
                                print(contents)
                                print()
                        case '2':
                            test1 = my_Predicate.Sentences('test1.txt')
                            test1.resolution()
                            test1.reindex()
                            print()
                        case '0':
                            print()
                            break
            case '2':
                while True:
                    show_menu2()
                    choice2 = input('选择你想实现的功能：')
                    match choice2:
                        case '1':
                            with open('test2.txt', encoding='utf-8') as file_obj:
                                contents = file_obj.read()
                                print(contents)
                                print()
                        case '2':
                            test1 = my_Predicate.Sentences('test2.txt')
                            test1.resolution()
                            test1.reindex()
                            print()
                        case '0':
                            print()
                            break
            case '3':
                while True:
                    show_menu2()
                    choice2 = input('选择你想实现的功能：')
                    match choice2:
                        case '1':
                            with open('test3.txt', encoding='utf-8') as file_obj:
                                contents = file_obj.read()
                                print(contents)
                                print()
                        case '2':
                            test1 = my_Predicate.Sentences('test3.txt')
                            test1.resolution()
                            test1.reindex()
                            print()
                        case '0':
                            print()
                            break
            case '0':
                print('感谢使用，程序结束')
                break
