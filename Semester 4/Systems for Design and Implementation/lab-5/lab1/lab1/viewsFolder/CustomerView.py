from django.http import JsonResponse
from rest_framework import status
from rest_framework.views import APIView
from django.views.decorators.csrf import csrf_exempt
from rest_framework.decorators import api_view
from rest_framework.response import Response
from django.db.models import Avg, Count
from rest_framework.generics import  GenericAPIView,ListAPIView
from rest_framework.viewsets import ModelViewSet

from lab1.models import Customers
from lab1.serializers import CustomerFilterSerializer, CustomerSerializer, CustomerDetailSerializer


class CustomerAPIView(APIView):
    @api_view(['GET', 'POST'])
    def customer_list(request, format=None):

        if request.method == 'GET':
            customers = Customers.objects.all()
            serializer = CustomerSerializer(customers, many=True)

            return Response(serializer.data)

        if request.method == 'POST':
            serializer = CustomerSerializer(data=request.data)

            if serializer.is_valid():
                serializer.save()
                return Response(serializer.data, status=status.HTTP_201_CREATED)
            print(serializer.errors)
            return Response(status=status.HTTP_404_NOT_FOUND)

    @api_view(['GET', 'PUT', 'DELETE'])
    def customer_detail(request, id, format=None):

        try:
            customers = Customers.objects.get(pk=id)
        except Customers.DoesNotExist:
            return Response(status=status.HTTP_404_NOT_FOUND)

        if request.method == 'GET':
            serializer = CustomerDetailSerializer(customers)
            return Response(serializer.data)

        elif request.method == 'PUT':
            serializer = CustomerSerializer(customers, data=request.data)
            if serializer.is_valid():
                serializer.save()
                return Response(serializer.data)
            else:
                return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

        elif request.method == 'DELETE':
            customers.delete()
            return Response(status=status.HTTP_204_NO_CONTENT)

    @api_view(['GET'])
    def customer_filtered_list(request, year, format=None):

        if request.method == 'GET':

            customers = Customers.objects.filter(year_of_birth__gt=year)

            serializer = CustomerFilterSerializer(customers, many=True)

            return Response(serializer.data)

