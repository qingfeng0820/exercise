rm -r TestModel/migrations
python manage.py migrate
python manage.py makemigrations TestModel
python manage.py migrate TestModel

