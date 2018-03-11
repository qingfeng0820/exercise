Directory Structure:
```shell
django-admin.py startproject HelloWorld
```

```shell
HelloWorld
|-- HelloWorld
|   |-- __init__.py
|   |-- settings.py
|   |-- urls.py
|   |-- wsgi.py
|   `-- views.py
`-- manage.py
```


```shell
django-admin.py startapp TestModel
```

```shell
HelloWorld
|-- HelloWorld
|   |-- __init__.py
|   |-- settings.py
|   |-- urls.py
|   |-- wsgi.py
|   `-- views.py
|-- TestModel
|   |-- __init__.py
|   |-- admin.py
|   |-- models.py
|   |-- tests.py
`-- manage.py
```



create db

```shell
python manage.py migrate
```

update db
```shell
python manage.py makemigrations TestModel   # show the updates
python manage.py migrate TestModel          # update tables in TestModel
```


Test: 
```shell
python manage.py runserver 0.0.0.0:8000
```


Django Refer <http://www.runoob.com/django/django-tutorial.html>

Django Restful Framework Refer <http://www.django-rest-framework.org>

Restful Client: <https://httpie.org/doc>

Make Sublime to be python IDE <http://www.cnblogs.com/dolphin0520/archive/2013/04/29/3046237.html>


Install mysqlclient issue on Mac:
  ImportError: dlopen(/usr/local/lib/python2.7/site-packages/_mysql.so, 2): Library not loaded: libmysqlclient.18.dylib
  Referenced from: /usr/local/lib/python2.7/site-packages/_mysql.so
  Reason: image not found
Why?
  how _mysql.so find libmysqlclient.18.dylib
  % otool -L /Library/Python/2.7/site-packages/_mysql.so
   /Library/Python/2.7/site-packages/_mysql.so:
    libmysqlclient.18.dylib (compatibility version 18.0.0, current version 18.0.0)
    /usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 169.3.0)
Solution:
  % sudo install_name_tool -change libmysqlclient.18.dylib /usr/local/mysql/lib/libmysqlclient.18.dylib /Library/Python/2.7/site-packages/_mysql.so
Then:
   % otool -L /Library/Python/2.7/site-packages/_mysql.so                                                                                      
   /Library/Python/2.7/site-packages/_mysql.so:
    /usr/local/mysql/lib/libmysqlclient.18.dylib (compatibility version 18.0.0, current version 18.0.0)
    /usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 169.3.0)
