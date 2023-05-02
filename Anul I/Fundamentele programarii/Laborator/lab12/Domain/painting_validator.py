from Domain.painting import Painting


class PaintingValidator:
    """
    Defineste validatorul pentru obiecte de tip tablou (Painting)
    """

    @staticmethod
    def validate(other: Painting):
        """
        Verifica validitatea atributelor unui obiect tablou (Painting)
        :param other: obiectul de verificat, obiect al clasei Painting
        :raises: ValueError pentru date invalide
        :return: None
        """

        errors = ''
        try:
            verify_id = int(other.id)
        except:
            errors += '\nID-ul introdus nu este un numar.'

        if other.title == '':
            errors += '\nTitlul tabloului nu poate fi gol.'

        try:
            other.price = int(other.price)
            if other.price < 1:
                errors += '\nPretul nu poate fi mai mic de 1 leu.'
        except:
            errors += '\nPretul tabloului introdus nu este un numar.'

        try:
            other.year = int(other.year)
            if other.year < 1:
                errors += '\nAnul nu poate fi negativ sau 0.'
        except:
            errors += '\nAnul introdus nu este un numar.'

        if len(errors):
            raise ValueError(errors)

        return other
