from Domain.artist_validator import ArtistValidator
from Domain.painting_validator import PaintingValidator
from Service.artist_service import ArtistService
from Service.painting_service import PaintingService
from Tests.run_all_tests import run_all_tests
from UserInterface.console import Console
from Repository.file_repository import FileRepository


def run_database():

    artist_repo = FileRepository('artists.txt')
    artist_val = ArtistValidator()
    painting_repo = FileRepository('paintings.txt')
    painting_val = PaintingValidator()

    painting_service = PaintingService(painting_repo, painting_val, artist_repo)
    artist_service = ArtistService(artist_repo, artist_val)

    user_interface = Console(artist_service, painting_service)
    user_interface.run_console()


run_all_tests()
run_database()
