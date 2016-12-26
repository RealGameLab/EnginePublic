	using System;
	using System.Data.SqlClient;

	namespace UnrealGameSync
	{
		static partial class Program
		{
			static Program()
			{
				SqlConnectionStringBuilder SqlConnectionStringBuilder = new SqlConnectionStringBuilder();
				SqlConnectionStringBuilder.DataSource = "ENGINESERVER\\SQLEXPRESS";
				SqlConnectionStringBuilder.UserID = "sa";
				SqlConnectionStringBuilder.Password = "admin";
				SqlConnectionStringBuilder.InitialCatalog = "UnrealGameSync";
				SqlConnectionStringBuilder.ConnectTimeout = 10;

				SqlConnectionString = SqlConnectionStringBuilder.ToString();
			}
		}
	}
