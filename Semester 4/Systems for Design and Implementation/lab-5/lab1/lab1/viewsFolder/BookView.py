from django.http import JsonResponse
from rest_framework import status
from rest_framework.views import APIView
from django.views.decorators.csrf import csrf_exempt
from rest_framework.decorators import api_view
from rest_framework.response import Response
from django.db.models import Avg, Count
from rest_framework.generics import  GenericAPIView,ListAPIView
from rest_framework.viewsets import ModelViewSet

from lab1.models import Books
from lab1.serializers import BookSerializer, BookDetailSerializer


class BookAPIView(APIView):
    @api_view(('GET', 'POST'))
    def books_list(request, format=None):

        # get all books
        # serialize them
        # return response (json)

        id = request.query_params.get('id')
        if request.method == 'GET':
            # get id
            if id:
                books = Books.objects.filter(id=id)
            # books = Books.objects.all()
            # serializer = BookSerializer(books, many=True)
            # return JsonResponse({"books": serializer.data})
            # return Response(serializer.data)
            else:
                books = Books.objects.all()
            serializer = BookSerializer(books, many=True)
            return Response(serializer.data)

        if request.method == 'POST':
            serializer = BookSerializer(data=request.data)
            if serializer.is_valid():
                serializer.save()
                return Response(serializer.data, status=status.HTTP_201_CREATED)
            else:
                print(serializer.errors)
                return Response(status=status.HTTP_404_NOT_FOUND)

    @api_view(['GET', 'PUT', 'DELETE'])
    def books_detail(request, id, format=None):
        try:
            books = Books.objects.get(pk=id)
        except Books.DoesNotExist:
            return Response(status=status.HTTP_404_NOT_FOUND)

        if request.method == 'GET':
            # get id
            serializer = BookDetailSerializer(books)
            return Response(serializer.data)

        if request.method == 'PUT':
            # update id
            serializer = BookDetailSerializer(books, data=request.data)
            if serializer.is_valid():
                serializer.save()
                return Response(serializer.data)
            else:
                return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

        if request.method == 'DELETE':
            books.delete()
            return Response(status=status.HTTP_204_NO_CONTENT)

