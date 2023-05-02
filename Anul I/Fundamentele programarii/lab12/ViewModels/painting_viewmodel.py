from Domain.artist import Artist
from Domain.painting import Painting


class PaintingViewModel:
    def __init__(self, given_painting: Painting, given_artist: Artist):
        self.__painting = given_painting
        self.__artist = given_artist

    def __str__(self):
        return f'ID: {self.__painting.id} | Tabloul "{self.__painting.title}" \n--->pictat de artistul {self.__artist.name} \n--->in anul {self.__painting.year}\n--->licitat la pretul de {self.__painting.price} lei.'
