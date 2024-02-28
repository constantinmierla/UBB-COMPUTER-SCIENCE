class Validarefilm:
    def valideaza_film(self, film):
        erori = ""
        if film.get_id() < 0:
            erori += "id film invalid\n"
        if film.get_title() == "":
            erori += "titlu film invalid\n"
        if film.get_gen() == "":
            erori += "gen film invalid\n"
        if film.get_desc() == "":
            erori += "gen descriere invalid\n"
        if len(erori) > 0:
            raise Exception(erori)