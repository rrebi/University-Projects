from django.http import JsonResponse
from rest_framework import status
from rest_framework.views import APIView

from .models import Books
from .models import Publisher
from .models import Customers
from .serializers import BookSerializer, BookDetailSerializer, PublisherDetailSerializer
from .serializers import PublisherSerializer
from .serializers import CustomerSerializer
from .serializers import CustomerFilterSerializer
from rest_framework.decorators import api_view
from rest_framework.response import Response

# A request handler that returns the relevant template and content - based on the request from the user
# takes http requests and returns http response, like HTML documents

class BookAPIView(APIView):
    @api_view(('GET', 'POST'))
    def books_list(request, format=None):

        # get all books
        # serialize them
        # return response (json)

        id = request.query_params.get('id')
        stars = request.query_params.get('stars')
        if request.method == 'GET':
            #get id
            if id:
                # Filter by ID
                # .../books/?id=X
                books = Books.objects.filter(id=id)
            #books = Books.objects.all()
            #serializer = BookSerializer(books, many=True)
            # return JsonResponse({"books": serializer.data})
            #return Response(serializer.data)
            elif stars:
                # .../cars/?productionyear=X
                # WILL RETRIEVE BOOKS WITH STARS > given stars in url
                books = Books.objects.filter(stars__gt=stars)

            else:
                # No filters applied, return all books
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
            #books_data = request.data
            #new_book = Books.objects.create(publisher=Publisher.objects.get(publisher=books_data['publisher']),
            #                             name=books_data['name'],
            #                             description=books_data['description'],
            #                             author=books_data['author'],
            #                             review=books_data['review'],
            #                             stars=books_data['stars'])
            #new_book.save()
            #serializer = BookSerializer(new_book)
            #return Response(serializer.data, status=status.HTTP_201_CREATED)



    @api_view(['GET', 'PUT', 'DELETE'])
    def books_detail(request, id, format=None):
        try:
            books = Books.objects.get(pk=id)
        except Books.DoesNotExist:
            return Response(status=status.HTTP_404_NOT_FOUND)

        if request.method == 'GET':
            #get id
            serializer = BookDetailSerializer(books)
            return Response(serializer.data)

        if request.method == 'PUT':
            #update id
            serializer = BookDetailSerializer(books, data=request.data)
            if serializer.is_valid():
                serializer.save()
                return Response(serializer.data)
            else:
                return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

        if request.method == 'DELETE':
            books.delete()
            return Response(status=status.HTTP_204_NO_CONTENT)

class PublisherAPIView(APIView):
    @api_view(['GET', 'POST'])
    def publisher_list(request, format=None):
        if request.method == 'GET':
            publisher = Publisher.objects.all()
            serializer = PublisherSerializer(publisher, many=True)

            return Response(serializer.data)

        if request.method == 'POST':
            serializer = PublisherSerializer(data=request.data)

            if serializer.is_valid():
                serializer.save()
                return Response(serializer.data, status=status.HTTP_201_CREATED)
            print(serializer.errors)
            return Response(status=status.HTTP_404_NOT_FOUND)


    @api_view(['GET','PUT', 'DELETE'])
    def publisher_detail(request, id, format=None):

        try:
            publisher = Publisher.objects.get(pk=id)
        except Publisher.DoesNotExist:
            return Response(status=status.HTTP_404_NOT_FOUND)

        if request.method == 'GET':
            serializer = PublisherDetailSerializer(publisher)
            return Response(serializer.data)

        elif request.method == 'PUT':
            #update
            serializer = PublisherSerializer(publisher, data=request.data)
            if serializer.is_valid():
                serializer.save()
                return Response(serializer.data)
            else:
                return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

        elif request.method == 'DELETE':
            publisher.delete()
            return Response(status=status.HTTP_204_NO_CONTENT)


class CustomerAPIView(APIView):
    @api_view(['GET', 'POST'])
    def custromer_list(request, format=None):

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

    @api_view(['GET','PUT', 'DELETE'])
    def customer_detail(request,id, format=None):

        try:
            customers = Customers.objects.get(pk=id)
        except Customers.DoesNotExist:
            return Response(status=status.HTTP_404_NOT_FOUND)

        if request.method == 'GET':
            serializer = CustomerSerializer(customers)
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
    def customerfiltered_list(request, year, format=None):

        if request.method == 'GET':

            customers = Customers.objects.filter(year_of_birth__gt=year)

            serializer = CustomerFilterSerializer(customers, many=True)

            return Response(serializer.data)
