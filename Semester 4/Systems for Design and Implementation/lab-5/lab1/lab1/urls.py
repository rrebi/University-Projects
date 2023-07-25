from django.contrib import admin
from django.urls import path
from lab1 import views
from rest_framework.urlpatterns import format_suffix_patterns

from drf_spectacular.views import SpectacularAPIView, SpectacularSwaggerView, SpectacularRedocView
from rest_framework import routers
from rest_framework_swagger.views import get_swagger_view
from rest_framework import permissions

from lab1.viewsFolder import BookView, PublisherView, CustomerView, BooksSoldView, StatisticsView, BulkAddView

# When a user requests a URL, Django decides which view it will send it to.

urlpatterns = [
path('api/schema/', SpectacularAPIView.as_view(), name='schema'),
    path('api/schema/swagger-ui/', SpectacularSwaggerView.as_view(url_name='schema'), name='swagger-ui'),
    path('api/schema/redoc/', SpectacularRedocView.as_view(url_name='schema'), name='redoc'),
    path("admin/", admin.site.urls),
    path("books/", BookView.BookAPIView.books_list),
    path("books/<int:id>", BookView.BookAPIView.books_detail),
    path('publisher/', PublisherView.PublisherAPIView.publisher_list),
    path('publisher/<int:id>', PublisherView.PublisherAPIView.publisher_detail),
    path('customers/', CustomerView.CustomerAPIView.customer_list),
    path('customers/<int:id>', CustomerView.CustomerAPIView.customer_detail),
    path('customers/filtered/<int:year>', CustomerView.CustomerAPIView.customer_filtered_list),
    path('sold/', BooksSoldView.BooksSoldAPIView.books_sold_list),
    path('sold/<int:id>', BooksSoldView.BooksSoldAPIView.books_sold_detail),
    path('books/<int:id>/customers', BooksSoldView.BooksSoldAPIView.books_sold_list),
    path("publisher/statistics/", StatisticsView.Statistics.statistics_publishers, name='stat_publisher'),
    path("customers/statistics/", StatisticsView.Statistics.statistics_customers, name='stat_customers'),
    path("publisher/to/books/", BulkAddView.BulkAddView.bulkAddPublisherToBook)
]

urlpatterns = format_suffix_patterns(urlpatterns)
