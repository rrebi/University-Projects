from django.http import JsonResponse
from rest_framework import status
from rest_framework.views import APIView
from django.views.decorators.csrf import csrf_exempt
from rest_framework.decorators import api_view
from rest_framework.response import Response
from django.db.models import Avg, Count
from rest_framework.generics import  GenericAPIView,ListAPIView
from rest_framework.viewsets import ModelViewSet

from lab1.models import Publisher, Books


class BulkAddView(APIView):
    @csrf_exempt
    @api_view(['POST'])
    def bulkAddPublisherToBook(request):
        book_id_new_publisher_list = request.data.get('book_id_new_publisher_list')

        # Loop through the list of book ids and new publishers to update
        for item in book_id_new_publisher_list:
            books = Books.objects.get(id=item['book_id'])
            books.publisher = Publisher.objects.get(publisher=item['new_publisher'])
            books.save()

        return Response({'message': 'Books updated successfully.'})
