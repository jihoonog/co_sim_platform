/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2019 University of Alberta
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author:  Evandro de Souza <evandro@ualberta.ca>
 * Date:    2019.05.12
 * Company: University of Alberta/Canada - Computing Science
 *
 * Based on code of default-simulator-impl.c from Mathieu Lacage <mathieu.lacage@sophia.inria.fr>, and
 * based on code of distributed-simulator-impl.c from George Riley <riley@ece.gatech.edu>
 *
 */

#ifndef SMARTGRID_DEFAULT_SIMULATOR_IMPL_H
#define SMARTGRID_DEFAULT_SIMULATOR_IMPL_H

#include "simulator-impl.h"
#include "scheduler.h"
#include "event-impl.h"
#include "system-thread.h"
#include "system-mutex.h"

#include "ptr.h"

#include <list>

/**
 * \file
 * \ingroup simulator
 * ns3::SmartgridDefaultSimulatorImpl declaration.
 */

namespace ns3 {

/**
 * \ingroup simulator
 *
 * The default single process simulator implementation.
 */
class SmartgridDefaultSimulatorImpl : public SimulatorImpl
{
public:
  /**
   *  Register this type.
   *  \return The object TypeId.
   */
  static TypeId GetTypeId (void);

  /** Constructor. */
  SmartgridDefaultSimulatorImpl ();
  /** Destructor. */
  ~SmartgridDefaultSimulatorImpl ();

  // Inherited
  virtual void Destroy ();
  virtual bool IsFinished (void) const;
  virtual void Stop (void);
  virtual void Stop (const Time &delay);
  virtual EventId Schedule (const Time &delay, EventImpl *event);
  virtual void ScheduleWithContext (uint32_t context, const Time &delay, EventImpl *event);
  virtual EventId ScheduleNow (EventImpl *event);
  virtual EventId ScheduleDestroy (EventImpl *event);
  virtual void Remove (const EventId &id);
  virtual void Cancel (const EventId &id);
  virtual bool IsExpired (const EventId &id) const;
  virtual void Run (void);
  virtual Time Now (void) const;
  virtual Time GetDelayLeft (const EventId &id) const;
  virtual Time GetMaximumSimulationTime (void) const;
  virtual void SetScheduler (ObjectFactory schedulerFactory);
  virtual uint32_t GetSystemId (void) const;
  virtual uint32_t GetContext (void) const;
  virtual uint64_t GetEventCount (void) const;

  // Smartgrid methods
  uint64_t NextTs (void) const;
  void RunUntil (const Time &checkTime);
  Time Next (void) const;


private:
  virtual void DoDispose (void);
  /** Move events from a different context into the main event queue. */
  void ProcessEventsWithContext (void);
  /** Process the next event. */
  void ProcessOneEvent (void);

  // Smartgrid methods
  bool IsLocalFinished (void) const;
  Scheduler::Event PeekNextEvent(void) const;
  Scheduler::Event RemoveNextEvent(void) const;

 
  /** Wrap an event with its execution context. */
  struct EventWithContext {
    /** The event context. */
    uint32_t context;
    /** Event timestamp. */
    uint64_t timestamp;
    /** The event implementation. */
    EventImpl *event;
  };
  /** Container type for the events from a different context. */
  typedef std::list<struct EventWithContext> EventsWithContext;
  /** The container of events from a different context. */
  EventsWithContext m_eventsWithContext;
  /**
   * Flag \c true if all events with context have been moved to the
   * primary event queue.
   */
  bool m_eventsWithContextEmpty;
  /** Mutex to control access to the list of events with context. */
  SystemMutex m_eventsWithContextMutex;

  /** Container type for the events to run at Simulator::Destroy() */
  typedef std::list<EventId> DestroyEvents;
  /** The container of events to run at Destroy. */
  DestroyEvents m_destroyEvents;

  /** Flag calling for the end of the simulation. */
  bool m_stop;
  /** The event priority queue. */
  Ptr<Scheduler> m_events;


  /** Next event unique id. */
  uint32_t m_uid;
  /** Unique id of the current event. */
  uint32_t m_currentUid;
  /** Timestamp of the current event. */
  uint64_t m_currentTs;
  /** Execution context of the current event. */
  uint32_t m_currentContext;
  /** The event count. */
  uint64_t m_eventCount;

  /**
   * Number of events that have been inserted but not yet scheduled,
   *  not counting the Destroy events; this is used for validation
   */
  int m_unscheduledEvents;

  /** Main execution thread. */
  SystemThread::ThreadId m_main;
};

} // namespace ns3

#endif /* SMARTGRID_DEFAULT_SIMULATOR_IMPL_H */
