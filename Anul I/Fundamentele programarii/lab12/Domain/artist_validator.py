from Domain.artist import Artist


class ArtistValidator:
    """
    Defineste validatorul obiectelor de tip pictor (Artist)
    """

    @staticmethod
    def validate(other: Artist):
        """
        Verifica validitatea atributelor unui obiect pictor (Artist)
        :param other: obiectul de verificat, obiect al clasei Artist
        :raises: ValueError pentru date invalide
        :return: None
        """

        errors = ''
        try:
            verify_id = int(other.id)
        except:
            errors += '\nID-ul introdus nu este un numar.'

        if other.name == '':
            errors += '\nNumele pictorului nu poate fi golf.'

        if other.style not in ['abstract', 'clasic', 'modern']:
            errors += '\nStilul introdus pentru artist poate fi doar abstract, clasic sau modern.'

        if len(errors):
            raise ValueError(errors)
