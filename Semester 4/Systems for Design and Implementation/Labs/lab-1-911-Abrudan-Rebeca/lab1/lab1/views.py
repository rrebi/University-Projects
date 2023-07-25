from django.http import JsonResponse
from .models import Books
from .serializers import BookSerializer
from rest_framework.decorators import api_view
from rest_framework.response import Response
from rest_framework import status

# A request handler that returns the relevant template and content - based on the request from the user
# takes http requests and returns http response, like HTML documents


@api_view(('GET', 'POST'))
def books_list(request, format=None):

    # get all books
    # serialize them
    # return response (json)

    if request.method == 'GET':
        books = Books.objects.all()
        serializer = BookSerializer(books, many=True)
        # return JsonResponse({"books": serializer.data})
        return Response(serializer.data)

    if request.method == 'POST':
        serializer = BookSerializer(data=request.data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data, status=status.HTTP_201_CREATED)


@api_view(['GET', 'PUT', 'DELETE'])
def books_detail(request, id, format=None):
    try:
        books = Books.objects.get(pk=id)
    except Books.DoesNotExist:
        return Response(status=status.HTTP_404_NOT_FOUND)

    if request.method == 'GET':
        serializer = BookSerializer(books)
        return Response(serializer.data)

    if request.method == 'PUT':
        serializer = BookSerializer(books, data=request.data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data)
        else:
            return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

    if request.method == 'DELETE':
        books.delete()
        return Response(status=status.HTTP_204_NO_CONTENT)
