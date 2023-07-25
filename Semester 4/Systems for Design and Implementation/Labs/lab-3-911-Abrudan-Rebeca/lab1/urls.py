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
    path('customers/', views.CustomerAPIView.customer_list),
    path('customers/<int:id>', views.CustomerAPIView.customer_detail),
    path('customers/filtered/<int:year>', views.CustomerAPIView.customer_filtered_list),
    path('buy/', views.BooksSoldAPIView.books_sold_list),
    path('buy/<int:id>', views.BooksSoldAPIView.books_sold_detail),
    path("publisher/statistics/", views.Statistics.statistics_publishers),
    path("customers/statistics/", views.Statistics.statistics_customers)
]

urlpatterns = format_suffix_patterns(urlpatterns)
