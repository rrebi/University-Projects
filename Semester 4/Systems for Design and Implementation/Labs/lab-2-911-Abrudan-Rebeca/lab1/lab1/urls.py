"""lab1 URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/4.1/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path
from lab1 import views
from rest_framework.urlpatterns import format_suffix_patterns

# When a user requests a URL, Django decides which view it will send it to.

urlpatterns = [
    path("admin/", admin.site.urls),
    path("books/", views.BookAPIView.books_list),
    path("books/<int:id>", views.BookAPIView.books_detail),
    path('publisher/', views.PublisherAPIView.publisher_list),
    path('publisher/<int:id>', views.PublisherAPIView.publisher_detail),
    path('customers/', views.CustomerAPIView.custromer_list),
    path('customers/<int:id>', views.CustomerAPIView.customer_detail),
    path('customersfiltered/<int:year>', views.CustomerAPIView.customerfiltered_list)
]

urlpatterns = format_suffix_patterns(urlpatterns)
