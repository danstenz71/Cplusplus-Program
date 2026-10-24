
# Developer: Dan Stenzel
# Date: October 2026
# Description: CRUD operations for the Grazioso Salvare animal database.


from pymongo import MongoClient


class AnimalShelter(object):
    """CRUD operations for the Animal collection in MongoDB."""

    def __init__(self, USER, PASS):
        HOST = 'localhost'
        PORT = 27017
        DB = 'aac'
        COL = 'animals'

        self.client = MongoClient(
            f"mongodb://{USER}:{PASS}@{HOST}:{PORT}/?authSource=admin"
        )

        self.database = self.client[DB]
        self.collection = self.database[COL]

    # Keep your create, read, update, and delete methods here.

    def create(self, data):
        try:
            if data is not None:
                result = self.collection.insert_one(data)
                return result.acknowledged
            return False
        except Exception as e:
            print("Error creating document:", e)
            return False

    def read(self, query):
        try:
            return list(self.collection.find(query))
        except Exception as e:
            print("Error reading documents:", e)
            return []

    def update(self, query, update_data):
        try:
            if not isinstance(update_data, dict):
                return 0

            if not any(key.startswith("$") for key in update_data):
                update_data = {"$set": update_data}

            result = self.collection.update_many(query, update_data)
            return result.modified_count
        except Exception as e:
            print("Error updating documents:", e)
            return 0

    def delete(self, query):
        try:
            result = self.collection.delete_many(query)
            return result.deleted_count
        except Exception as e:
            print("Error deleting documents:", e)
            return 0

