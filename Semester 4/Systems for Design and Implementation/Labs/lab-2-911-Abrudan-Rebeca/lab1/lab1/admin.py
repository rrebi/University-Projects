from django.contrib import admin
from .models import Books
from .models import Publisher
from .models import Customers

admin.site.register(Books)
admin.site.register(Publisher)
admin.site.register(Customers)
