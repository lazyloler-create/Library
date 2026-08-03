using System;
using System.Text.Json;
using System.IO;
using System.Net.Http;
using Microsoft.Data.Sqlite;

namespace LibraryManagement {
    class Program {

        private const string searchAPI = "https://openlibrary.org/search.json?";
        private static readonly HttpClient httpClient = new();

        static void Main(string[] args) {
            string connectionString = "Data Source=library.db";
            using var connection = new SqliteConnection(connectionString);
            connection.Open();

            string createTable = @"
                CREATE TABLE IF NOT EXISTS Books (
                    ISBN TEXT PRIMARY KEY,
                    Title TEXT NOT NULL,
                    Author TEXT DEFAULT 'Unknown',
                    Category TEXT DEFAULT 'General',
                    Description TEXT,
                    Year INTEGER,
                    Format TEXT DEFAULT 'Hardcover',
                    Pages INTEGER
                )";
            using var cmd = new SqliteCommand(createTable, connection);
            cmd.ExecuteNonQuery();
            Console.WriteLine("Database created!");

            int choice;

            //isbn is a 10 or 13 digit code that id's a book
            Console.WriteLine("\nLibrary options:");
            Console.WriteLine("1. Search by keyword");
            Console.WriteLine("2. Search by ISBN");
            Console.WriteLine("3. List all books");
            Console.WriteLine("0. Exit");
            do{
                Console.Write("\nEnter option (0-3): ");
                choice = Console.ReadLine();

                    case 1:
                        SearchByKeyword(connection);
                        break;
                    case 2
                        SearchByISBN(connection);
                        break;
                    case 3:
                        ListAllBooks(connection);
                        break;
                    case 0:
                        Console.WriteLine("Exiting program");
                        break;
                    default:
                        Console.WriteLine("Invalid option try again");
                        break;
            }while(choice); 
        }

        static void SearchByKeyword(SqliteConnection connection){
            Console.WriteLine("Enter a search keyword: ");
            string keyword = Console.ReadLine()?.Trim();

            if(string.IsNullOrWhiteSpace(keyword))
                return;

            var url = $"{searchAPI}q={Uri.EscapeDataString(keyword)}&limit=5";
            Console.WriteLine("Fetching data! \n");

            var response = httpClient.GetAsync(url).Result;
            string json = response.Content.ReadAsStringAsync().Result;
            var results = JsonSerializer.Deserialize<SearchResults>(json) ?? new SearchResults();
        }
    }
}
