/*
 * File: example.cpp
 * Created Date: Monday, November 25th 2019, 11:12:14 pm
 * Author: yusnows
 * -----
 * Last Modified: Tue Nov 26 2019
 * Modified By: yusnows
 * -----
 * Copyright (c) 2019 yusnows
 * 
 * All shall be well and all shall be well and all manner of things shall be well.
 * Nope...we're doomed!
 * -----
 * HISTORY:
 * Date      	By	Comments
 * ----------	---	----------------------------------------------------------
 */
#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>
#include "GL/glut.h"
using namespace std;
/*********************************************************
 * the code below is for render and window manager
 * ********************************************************/
typedef void (*CallbackFunction)();
typedef void (*KeyboardFunction)(unsigned char key, int x, int y);
typedef void (*ReshapeFunction)(int width, int height);
typedef void (*MouseButtonFunction)(int button, int state, int x, int y);
typedef void (*MouseMotionFunction)(int x, int y);
typedef void (*IdleFunction)(void);
typedef void (*TimerFunction)(int value);



class BlackBoard
{
public:
    void InitCommandLine(int *argc, char **argv);
    void InitWindowSize(int width, int height);
    void UpdateWindowSize(int width, int height);

    // ���ô��ڻ��ƻص�����
    void InitDisplayCallback(CallbackFunction callback);

    // ���ü����¼��ص�����
    void InitKeyboardCallback(KeyboardFunction callback);

    // ���ô��������¼��ص�����
    void InitReshapeCallback(ReshapeFunction callback);

    // ����������¼��ص�����
    void InitMouseButtonCallback(MouseButtonFunction callback);

    // ��������ƶ��¼��ص�����
    void InitMouseMotionCallback(MouseMotionFunction callback);

    // ���ÿ���״̬�ص�����
    void InitIdleCallback(IdleFunction callback);

    // ����һ����ʱ����ע�⣬ֻ�ᴥ��һ�Σ��������ڴ���
    // ��Ҫ���ڴ������ڻص������У��ٴ�����һ��ͬ���Ķ�ʱ��
    void InstallTimerCallback(unsigned int millis, TimerFunction callback, int value);

    // ��������ʾ���ڣ�������һ�Σ�֮�󣬽������¼�ѭ��
    void Show();

    // ��־������Ҫ���£�ͨ�������ݷ����仯����������Ҫ�󴰿��ػ�
    void Update();

    // ���º���ֻ���ڻ��ƻص������У�ͨ��ʱ���������Update��ϵͳ����Update-> �����ػ棨�¼�ѭ�����û��ƻص������� -> �����º�������ͼ��

    // ������ɫ��r/g/bΪ��ɫ������0-1֮�䣬
    // �紿��Ϊ1,0,0;
    // ����Ϊ1,1,1
    void SetColor(double r, double g, double b);
    // ����
    void Clear();
    // ������ͼ����ʾ����
    void Flush();

    // ���ߣ�����Ϊ�����˵��x��y����
    void DrawLine(int x1, int y1, int x2, int y2);

    // ��Բ������ΪԲԲ��x��y���뾶
    void DrawCircle(int x, int y, int r);

private:
    int _width, _height;
};

using std::cout;
using std::endl;

void BlackBoard::InitCommandLine(int *argc, char **argv)
{
    glutInit(argc, argv);
}

void BlackBoard::InitWindowSize(int width, int height)
{
    _width = width;
    _height = height;

    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(_width, _height);

    glutCreateWindow("BlackBoard");
}

void BlackBoard::UpdateWindowSize(int width, int height)
{
    _width = width;
    _height = height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void BlackBoard::InitDisplayCallback(CallbackFunction callback)
{
    glutDisplayFunc(callback);
}

void BlackBoard::InitKeyboardCallback(KeyboardFunction callback)
{
    glutKeyboardFunc(callback);
}

void BlackBoard::InitReshapeCallback(ReshapeFunction callback)
{
    glutReshapeFunc(callback);
}

void BlackBoard::InitMouseButtonCallback(MouseButtonFunction callback)
{
    glutMouseFunc(callback);
}

void BlackBoard::InitMouseMotionCallback(MouseMotionFunction callback)
{
    glutMotionFunc(callback);
}

void BlackBoard::InitIdleCallback(IdleFunction callback)
{
    glutIdleFunc(callback);
}

void BlackBoard::InstallTimerCallback(unsigned int millis, TimerFunction callback, int value)
{
    glutTimerFunc(millis, callback, value);
}

void BlackBoard::Show()
{
    glutMainLoop();
}

void BlackBoard::SetColor(double r, double g, double b)
{
    glColor3f(r, g, b);
}

void BlackBoard::Update()
{
    glutPostRedisplay();
}

void BlackBoard::DrawLine(int x1, int y1, int x2, int y2)
{
    glBegin(GL_LINES);
    glVertex2f(GLfloat(x1) / _width * 2, GLfloat(y1) / _height * 2);
    glVertex2f(GLfloat(x2) / _width * 2, GLfloat(y2) / _height * 2);
    glEnd();
}

void BlackBoard::DrawCircle(int x, int y, int r)
{
    const int CIRCLE_SEGMENTATION = 360;
    const GLfloat Pi = 3.1415926536f;

    GLfloat x0 = GLfloat(x) / _width * 2;
    GLfloat y0 = GLfloat(y) / _height * 2;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < CIRCLE_SEGMENTATION; ++i)
    {
        glVertex2f(x0 + GLfloat(r) * cos(2 * Pi * i / CIRCLE_SEGMENTATION) / _width * 2, y0 + GLfloat(r) * sin(2 * Pi * i / CIRCLE_SEGMENTATION) / _height * 2);
    }
    glEnd();
}

void BlackBoard::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void BlackBoard::Flush()
{
    glFlush();
}
/*********************************************************
 * the code above is for render and window manager
 * ********************************************************/

/*********************************************************
 * the code below is for 2D geometry manager. 
 * it is what you need to implement.
 * !Notify: this is just a example class, it doesn't mean
 * you don't need implement other class(es).
 * Just implement the function in your free.
 * ********************************************************/

class FigureManager
{
public:
    static FigureManager &handle()
    {
        static FigureManager manager;
        return manager;
    }
    // FigureManager����������
    virtual ~FigureManager() {}
    // FigureManager��ӿ�.
public:
    void input(std::istream& is)
    {
        int temp;
        int data;
        while (is >> temp && temp !=0 )
        {
                v.push_back(temp);
                switch (temp)
                {
                case 1:
                {
                    for (int i = 0; i < 3; ++i)
                    {
                        is >> data;
                        v.push_back(data);
                    }

                    break;
                }
                case 2:
                {
                    for (int i = 0; i < 4; ++i)
                    {
                        is >> data;
                        v.push_back(data);
                    }
                    break;
                }
                case 3:
                {
                    for (int i = 0; i < 4; ++i)
                    {
                        is >> data;
                        v.push_back(data);
                    }
                    break;
                }
                default:
                    break;
                }
                m.push_back(v);
                v.clear();




        }
    }

    void display(BlackBoard& board)
    {
        int msize;
        msize = m.size();
        for (int i = 0; i < msize; ++i)
        {
            int flag = m[i][0];
            
            switch (flag)
            {
            case 1:
            {
                int x = m[i][1];
                int y = m[i][2];
                int r = m[i][3];
                board.DrawCircle(x, y, r);
            
                break;
            }
            case 2:
            {
                int x1 = m[i][1];
                int y1 = m[i][2];
                int x2 = m[i][3];
                int y2 = m[i][4];
                board.DrawLine(x1, y1, x2, y2);
                break;
            }
            case 3:
            {
                int left = m[i][1];
                int top = m[i][2];
                int right = m[i][3];
                int bottom = m[i][4];
                board.DrawLine(left, bottom, left, top);
                board.DrawLine(right, bottom, right, top);
                board.DrawLine(left, bottom, right, bottom);
                board.DrawLine(left, top, right, top);
                break;
            }
            default:
                break;
            }
            
        }
    }
    void print(std::ostream& out)
    {
        int msize;
        msize = m.size();
        for (int i = 0; i < msize; ++i)
        {
            int flag = m[i][0];

            switch (flag)
            {
            case 1:
            {
                int x = m[i][1];
                int y = m[i][2];
                int r = m[i][3];
                out << "Circle" << "{" << "center_X: " << x << ", " << "center_Y: " << y << ", " << "radius: " << r << "}" << endl ;

                break;
            }
            case 2:
            {
                int x1 = m[i][1];
                int y1 = m[i][2];
                int x2 = m[i][3];
                int y2 = m[i][4];
                out << "Line" << "{" << "point1_X: " << x1 << ", " << "point1_Y: " << y1 << ", " << "point2_X: " << x2 << ", " << "point2_Y: " << y2 << "}" << endl;
                break;
            }
            case 3:
            {
                int left = m[i][1];
                int top = m[i][2];
                int right = m[i][3];
                int bottom = m[i][4];
                out << "Rectangle" << "{" << "left: " << left << ", " << "top: " << top << ", " << "right: " << right << ", " << "bottom: " << bottom << "}" << endl;
                break;
            }
            default:
                break;
            }

        }
    }
private:
    vector <int> v;
    vector <vector<int>> m;
}; // class FigureManager�ඨ�����.

// ������ʵ����ҪһЩ��Ҫ�ĳ�ʼ�����ɷ�����������У�main���������
// ���û�У������
void InitiateFigureManager()
{
}

/*********************************************************
 * the code above is for 2D geometry manager. 
 * it is what you need to implement.
 * !Notify: this is just a example class, it doesn't mean
 * you don't need implement other class(es).
 * Just implement the function in your free.
 * ********************************************************/

/*********************************************************
 * the code below is program main function. 
 * ********************************************************/
// �ṩ��ͼ�����Ķ���
BlackBoard board;
// �ɺ���
void ReshapeCallback(int width, int height)
{
    board.UpdateWindowSize(width, height);
}
// �������ڴ����������Ļص�������ڣ�����ֻ������һ���£���q�˳����򣬿ɺ���
// ע�⣬����ļ��������Ǵ��ڵļ������룬�����������е�
void KeyboardCallback(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'q':
        exit(0);
        break;
    }
}
// �������ڻ��ƵĻص�������ڣ����ջ����FigureManager��display����
// ������ҵ����Ķ�DisplayCallback������ͼ��Ӧ��FigureManager����ɡ�
void DisplayCallback()
{
    board.Clear();

    FigureManager::handle().display(board);

    board.Flush();
}
#if 1
int main(int argc, char *argv[])
{
    // ������ʵ����ҪһЩ��Ҫ�ĳ�ʼ�����ɷ�����������У�main���������
    // ���û�У������
    InitiateFigureManager();

    // ������л����뷽ʽ��
    // 1����test.txt�ļ����룬�Է������ʱ���������ʱ��
    // 2�������������룬�԰�����û����ȫ��д�ô���ʱ���޷���test.txt����

    //cout << "input data" << endl;
#if 1
    std::ifstream input("test.txt");  
    if (!input.is_open())
    { 
        std::cout << "Error opening input file"; 
        exit(1); 
    }  
    FigureManager::handle().input(input);
#else
    FigureManager::handle().input(std::cin);
   // cout << "success 1!" << endl;
#endif

    // ���´������ڳ�ʼ�����ڵȡ��ɺ���
    board.InitCommandLine(&argc, (char **)argv);
    board.InitWindowSize(1000, 800);

    board.InitDisplayCallback(DisplayCallback);
    board.InitKeyboardCallback(KeyboardCallback);
    board.InitReshapeCallback(ReshapeCallback);
    FigureManager::handle().print(std::cout);
   // cout << "success 2!" << endl;
    board.Show();
   // cout << "success 3!" << endl;
    
    return 0;
}
#endif

