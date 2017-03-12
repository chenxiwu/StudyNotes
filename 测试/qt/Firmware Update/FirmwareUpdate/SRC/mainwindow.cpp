#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "curl.h"

int curlTest2();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    curlTest2();
}

MainWindow::~MainWindow()
{
    delete ui;
}

size_t process_data(void *buffer, size_t size, size_t nmemb, void *user_p) {
    FILE *fp = (FILE *)user_p;
    size_t return_size = fwrite(buffer, size, nmemb, fp);
    qDebug()<< (char *)buffer << endl;
    return return_size;
}

int curlTest2()
{
    // 初始化libcurl
    CURLcode return_code;
    return_code = curl_global_init(CURL_GLOBAL_ALL);
    if (CURLE_OK != return_code)    {
        qDebug() << "init libcurl failed." << endl;
        return -1;
    }

        // 获取easy handle
    CURL *easy_handle = curl_easy_init();
        if (NULL == easy_handle)
        {
            qDebug()  << "get a easy handle failed." << endl;
            curl_global_cleanup();
            return -1;
        }
        qDebug() << "Start...";

        FILE *fp = fopen("sy.html", "ab+");
        if (fp == NULL) {
            qDebug() << "File Open Error!";
            return -1;
        }

        // 设置easy handle属性
        curl_easy_setopt(easy_handle, CURLOPT_URL, "http://c.biancheng.net/cpp/html/314.html");
        curl_easy_setopt(easy_handle, CURLOPT_WRITEFUNCTION, &process_data);
        curl_easy_setopt(easy_handle, CURLOPT_WRITEDATA, fp);

        // 执行数据请求
        curl_easy_perform(easy_handle);
        // 释放资源
        fclose(fp);
        curl_easy_cleanup(easy_handle);
        curl_global_cleanup();

        return 0;
}
