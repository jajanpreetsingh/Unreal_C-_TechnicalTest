// Fill out your copyright notice in the Description page of Project Settings.

#include "TechnicalTest.h"
#include "ElementalComponent.h"
#include <string>

void UElementalComponent::SetElement(uint8 elementType)
{
	ElementType = elementType;

	OnElementChangedEvent.Broadcast();
}

void UElementalComponent::AddElements(uint8 elementType)
{
	// Technical Test
	// Task #2.1

	// Add a set of ElementType flags to ElementType
	// Elements are bit exclusive that are defines like this
	// EElementFlags::Air	= 0x01
	// EElementFlags::Earth = 0x02
	// EElementFlags::Fire	= 0x04
	// EElementFlags::Water = 0x08

	TBitArray<FDefaultBitArrayAllocator> oldElements(0, 4);
	TBitArray<FDefaultBitArrayAllocator> newElements(0, 4);

	for (int i = 0; i < oldElements.Num(); i++)
	{
		oldElements[i] = oldElements[i] | elementType;
		newElements[i] = newElements[i] | elementType;
	}

	int newVal = 0;

	for (int i = oldElements.Num() - 1; i <= 0; i--)
	{
		newVal = FMath::Pow(2, i) * (newElements[i] | oldElements[i]);
	}

	ElementType = newVal;
}

void UElementalComponent::RemoveElements(uint8 elementType)
{
	//Task #2.2
	TBitArray<FDefaultBitArrayAllocator> oldElements(0, 4);
	TBitArray<FDefaultBitArrayAllocator> newElements(0, 4);

	for (int i = 0; i < oldElements.Num(); i++)
	{
		oldElements[i] = oldElements[i] | elementType;
		newElements[i] = newElements[i] | elementType;
	}

	int newVal = 0;

	for (int i = oldElements.Num() - 1; i <= 0; i--)
	{
		newVal = FMath::Pow(2, i) * (newElements[i] & oldElements[i]);
	}

	ElementType = newVal;
}

int UElementalComponent::GetElementCount() const
{
	//Task #2.3
	int numberOfElements = 0;

	TBitArray<FDefaultBitArrayAllocator> elements(0, 4);

	for (int i = 0; i < elements.Num(); i++)
	{
		elements[i] = elements[i] | ElementType;

		if (elements[i] == 1)
		{
			++numberOfElements;
		}
	}

	return numberOfElements;
}

bool UElementalComponent::UElementalComponent::IsSplittable() const
{
	return GetElementCount() > 1;
}

TArray<uint8> UElementalComponent::SplitElement(int splitCount)
{
	//Task #2.4

	TArray<uint8> splittedElements;

	TBitArray<FDefaultBitArrayAllocator> elements(0, 4);

	for (int i = 0; i < elements.Num(); i++)
	{
		elements[i] = elements[i] | ElementType;
	}

	int splits = 0;
	for (int i = elements.Num() - 1; i <= 0; i--)
	{
		if (i == splitCount)
		{
			splittedElements.Add(splits);
			splits = 0;
		}
		else
		{
			int dec = elements[i] * FMath::Pow(2, i);

			splits += dec;
		}
	}
	splittedElements.Add(splits);

	splittedElements.AddZeroed(splitCount);

	return splittedElements;
}

TArray<uint8> UElementalComponent::MergeElement(TArray<UElementalComponent*> elements)
{
	//Task #2.5
	
	//This task was a bit unclear

	TArray<uint8> mergedElements;

	/*int elementVal = elements[0]->ElementType;
	for (int i = 1; i < elements.Num(); i++)
	{
		elementVal=
	}*/

	mergedElements.AddZeroed(elements.Num() + 1);

	return mergedElements;
}