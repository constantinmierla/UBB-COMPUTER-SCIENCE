from DOMAIN.entities import Bicicleta


class RepoFile:
    def __init__(self, file):
        self.__file_path = file

    def open_for_read(self):
        input_file = open(self.__file_path, "r+")
        return input_file

    def open_for_write(self):
        output_file = open(self.__file_path, "w")
        return output_file

    @staticmethod
    def close_file(file):
        file.close()

    @staticmethod
    def delete_all_data_from_file(file):
        file.seek(0)
        file.truncate()


class Repo:
    def __init__(self):
        self.__elements = []

    def load_from_file(self, file):
        input_file = file.open_for_read()

        for line in input_file:
            line = line.strip()
            parts = line.split(', ')

            # datele sunt:
            # id_bicicleta, tip, pret
            id_bicicleta = int(parts[0])
            tip = parts[1]
            pret = float(parts[2])

            bicicleta = Bicicleta(id_bicicleta, tip, pret)

            self.__elements.append(bicicleta)

        file.close_file(input_file)

    def write_in_file(self, file):
        output_file = file.open_for_write()
        file.delete_all_data_from_file(output_file)

        nr_el = self.get_numar()
        for i in range(0, nr_el):
            el = self.get_element_from_position(i)

            informatie = ""
            informatie += str(el.get_id())
            informatie += ", "
            informatie += str(el.get_tip())
            informatie += ", "
            informatie += str(el.get_pret())
            informatie += "\n"

            output_file.write(informatie)

        file.close_file(output_file)

    def get_numar(self):
        return len(self.__elements)

    def get_element_from_position(self, k):
        return self.__elements[k]

    def copiere_lista_noua(self, lista_noua):
        self.__elements = lista_noua
