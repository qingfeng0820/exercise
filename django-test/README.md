Setup:
```shell
django-admin.py startproject HelloWorld
```

```shell
$ cd HelloWorld/
$ tree
.
|-- HelloWorld
|   |-- __init__.py
|   |-- settings.py
|   |-- urls.py
|   `-- wsgi.py
`-- manage.py
```


```shell
django-admin.py startapp TestModel
```

```shell
HelloWorld
|-- TestModel
|   |-- __init__.py
|   |-- admin.py
|   |-- models.py
|   |-- tests.py
|   `-- views.py
```



Test: 
```shell
python manage.py runserver 0.0.0.0:8000
```
