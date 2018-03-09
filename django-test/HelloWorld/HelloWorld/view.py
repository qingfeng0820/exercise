# -*- coding: utf-8 -*-

from django.http import HttpResponse
from django.shortcuts import render


def hello(request):
    return HttpResponse("Hello world!")


def greet(request):
	context          = {}
	context['greet'] = 'Greet!'
	if 'q' in request.GET:
		context['greet'] += ' ' + request.GET['q']
	return render(request, 'greet.html', context)
