Setup:
```shell
django-admin.py startproject HelloWorld
```

```shell
.
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



Test: 
```shell
python manage.py runserver 0.0.0.0:8000
```
