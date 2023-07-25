from django.http import JsonResponse
from rest_framework import status
from rest_framework.views import APIView
from django.views.decorators.csrf import csrf_exempt

from rest_framework.decorators import api_view
from rest_framework.response import Response
from django.db.models import Avg, Count
from rest_framework.generics import  GenericAPIView,ListAPIView
from rest_framework.viewsets import ModelViewSet

from lab1.models import BookSold
from lab1.serializers import BooksSoldSerializer, BooksSoldDetailSerializer


class BooksSoldAPIView(APIView):
    @api_view(['GET', 'POST'])
    def books_sold_list(request, format=None):

        if request.method == 'GET':
            books_sold = BookSold.objects.all()
            serializer = BooksSoldSerializer(books_sold, many=True)

            return Response(serializer.data)

        if request.method == 'POST':
            serializer = BooksSoldSerializer(data=request.data)

            if serializer.is_valid():
                serializer.save()
                return Response(serializer.data, status=status.HTTP_201_CREATED)
            print(serializer.errors)
            return Response(status=status.HTTP_404_NOT_FOUND)

    @api_view(['GET', 'PUT', 'DELETE'])
    def books_sold_detail(request, id, format=None):

        try:
            books_sold = BookSold.objects.get(pk=id)
        except BookSold.DoesNotExist:
            return Response(status=status.HTTP_404_NOT_FOUND)

        if request.method == 'GET':
            serializer = BooksSoldDetailSerializer(books_sold)
            # serializer = CustomersBooksSerializer(books_sold)
            return Response(serializer.data)

        elif request.method == 'PUT':
            serializer = BooksSoldSerializer(books_sold, data=request.data)
            if serializer.is_valid():
                serializer.save()
                return Response(serializer.data)
            else:
                return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

        elif request.method == 'DELETE':
            books_sold.delete()
            return Response(status=status.HTTP_204_NO_CONTENT)

