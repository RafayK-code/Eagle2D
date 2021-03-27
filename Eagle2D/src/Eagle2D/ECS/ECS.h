#pragma once
//includes
#include "egpch.h"

#pragma warning(push)
#pragma warning(disable:4251)

namespace Eagle
{
	namespace ECS
	{
		//alias
		using EntityID = std::uint32_t;
		using ComponentType = std::uint8_t;

		//constants
		constexpr EntityID MAX_ENTITIES = 10000;
		constexpr ComponentType MAX_COMPONENTS = 32;

		//signature AKA component bitset
		using Signature = std::bitset<MAX_COMPONENTS>;

		//function to get the component ID of a new component
		inline ComponentType GetNewComponentTypeID()
		{
			static ComponentType id = 0;
			return id++;
		}

		//function to get the componend ID of a specified component
		template <typename T>
		inline ComponentType GetComponentTypeID() noexcept
		{
			static ComponentType typeID = GetNewComponentTypeID();
			return typeID;
		}

		//Component struct which will be inherited by all components
		struct EAGLE_API Component
		{
			virtual ~Component() {}
		};

		//Entity class
		class Entity
		{
		public:
			//function to add a component to this entity (component passed is not a reference meaning it can be passed in via initializer list)
			template <typename T, typename... TArgs>
			void AddComponent(TArgs&&... mArgs)
			{
				//create a new object and have the array point to the same block of memory for it
				_ComponentArray[GetComponentTypeID<T>()] = std::make_unique<T>(std::forward<TArgs>(mArgs)...);
				_Signature[GetComponentTypeID<T>()] = true;
			}

			template <typename T>
			T& GetComponent()
			{
				//get the data for each specific component requested
				return *static_cast<T*>(_ComponentArray[GetComponentTypeID<T>()].get());
			}

			Signature GetEntitySignature() const
			{
				//return the bitset of our entity
				return _Signature;
			}

		private:
			//array containing each component
			std::array<std::unique_ptr<Component>, MAX_COMPONENTS> _ComponentArray{};
			//signature of the entity (what components it has/does not have
			Signature _Signature;
		};

		//base system class, for other systems that are user-defined to inherit
		class EAGLE_API System
		{
		public:
			//set of all the entities, keep tracked of using the entityID
			std::unordered_set<EntityID> _Entities;
		};

		//Manager class
		//This class will manage all the systems and entities
		//It will keep track of entities via entity ID's that can be given to the user of this ECS on the client side
		//This is to avoid having conflicts where manager is used sometimes, and entity class is used other times by the user
		//Entities will only be managed by the manager class. The entity ID is a key used to access a specific entity
		//Systems will be added to a map of signatures and systems
		//The signature will determine what entities the system will iterate through and cares about
		class Manager
		{
		public:
			//function that gets called on startup
			void Init()
			{
				//fill our available entities queue
				for (EntityID entity = 0; entity < MAX_ENTITIES; entity++)
				{
					_AvailableEntities.push(entity);
				}

				EG_CORE_INFO("ECS Manager initialized.");
			}

			//This function returns an ID to the user
			EntityID CreateEntity()
			{
				//get an ID from our queue
				EntityID id = _AvailableEntities.front();
				//remove that id from our queue
				_AvailableEntities.pop();

				//create an instance of an entity and insert it into our map
				std::unique_ptr<Entity> entity = std::make_unique<Entity>();
				_Entities.insert({ id, std::move(entity) });

				//return the ID to the user
				return id;
			}

			//This function destroys an entity given the id of that entity
			void DestroyEntity(EntityID entity)
			{
				//erase the entity from our map
				_Entities.erase(entity);

				//go through each system and remove the entity
				for (auto const& pair : _Systems)
				{
					pair.second->_Entities.erase(entity);
				}

				//push the ID back into the queue
				_AvailableEntities.push(entity);
			}

			//Adds a type of component to an entity
			template <typename T, typename... TArgs>
			void AddComponent(EntityID entity, TArgs&&... mArgs)
			{
				//calls the add component function for the entity
				_Entities[entity]->AddComponent<T>(std::forward<TArgs>(mArgs)...);

				Signature signature = _Entities[entity]->GetEntitySignature();

				//go through our systems, and if the entity doesnt have all the components the system requires, the system will ignore it
				for (auto const& pair : _Systems)
				{
					if ((signature & pair.first) == pair.first)
					{
						pair.second->_Entities.insert(entity);
					}

					else
					{
						pair.second->_Entities.erase(entity);
					}
				}
			}

			//Gets a reference to a component from an entity
			template <typename T>
			T& GetComponent(EntityID entity)
			{
				//look up the entity and call the get component function
				return _Entities[entity]->GetComponent<T>();
			}

			//Gets a component type (used to register a signature to a system mainly)
			template <typename T>
			ComponentType GetComponentType()
			{
				return GetComponentTypeID<T>();
			}

			//returns a shared pointer of generic type T (system passed in), takes in a signature
			template <typename T>
			std::shared_ptr<T> AddSystem(Signature signature)
			{
				//create a system of type T and initialize it
				std::shared_ptr<T> system = std::make_shared<T>(this);
				//insert this into our map along with the signature
				_Systems.insert({ signature, system });

				//return the system back to user
				return system;
			}

		private:
			//map of signatures to shared pointers of systems. This map is used to associate a signature with each system
			std::unordered_map<Signature, std::shared_ptr<System>> _Systems;

			//queue of available entites (FIFO)
			std::queue<EntityID> _AvailableEntities;
			//map of entity IDs to unique pointers of entites. Using this map, entities can be oeprated on givin an entity key from user
			std::unordered_map<EntityID, std::unique_ptr<Entity>> _Entities;
		};
	}
}

#pragma warning(pop)