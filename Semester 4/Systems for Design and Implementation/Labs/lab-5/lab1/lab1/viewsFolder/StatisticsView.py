from django.http import JsonResponse
from rest_framework import status
from rest_framework.views import APIView
from django.views.decorators.csrf import csrf_exempt
from rest_framework.decorators import api_view
from rest_framework.response import Response
from django.db.models import Avg, Count
from rest_framework.generics import  GenericAPIView,ListAPIView
from rest_framework.viewsets import ModelViewSet

from lab1.models import Customers, Publisher
from lab1.serializers import StatisticsSerializerCustomer, StatisticsSerializerPublisher


class Statistics(APIView):
    @api_view(['GET'])
    def statistics_publishers(request):
        # publishers ordered by the average of their books stars
        statistics = Publisher.objects.annotate(
            avg_stars=Avg('books__stars'),
            book_count=Count('books')
        ).order_by('-avg_stars')

        serializer = StatisticsSerializerPublisher(statistics, many=True)
        return Response(serializer.data)

    # done in class
    @api_view(['GET'])
    def statistics_customers(request):
        # customers ordered by the average of their books bought amount
        statistics = Customers.objects.annotate(
            avg_amount=Avg('customers_id__amount'),
            books_sold_count=Count('customers_id')
        ).order_by('-avg_amount')

        serializer = StatisticsSerializerCustomer(statistics, many=True)
        return Response(serializer.data)

